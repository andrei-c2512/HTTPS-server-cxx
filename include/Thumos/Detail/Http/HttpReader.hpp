#pragma once
#include "Thumos/Core/MessageReader.hpp"
#include "Thumos/Detail/Http/HttpMessage.hpp"
#include "asio/ssl.hpp"


namespace thm::detail{
    template<IsSocket socketType>
    class HttpReader : public core::AbstractMessageReader<socketType> {
    public:
            HttpReader(bool& canWriteFlag) 
                    :core::AbstractMessageReader<socketType>(canWriteFlag)
            {
                    //how many kbs I want
                    const int kb = 4;
                    bufferSize = kb * 1048;
                    buffer.resize(bufferSize);
            }

            void start(socketType& socket) override
            {
                    readHeader(socket);
            }
    protected:
            void readHeader(socketType& socket)
            {
            //ConsoleLog::info("Started reading");
            //I hate how it doesn't approve of std::string as a buffer
            //edit: nvm I switched to C++ 20 and buffer.data() changed from const char* to char*
            socket.async_read_some(asio::buffer(buffer.data(), bufferSize),
                    [this, &socket](std::error_code ec, std::size_t length) {
                            if (!ec) {
                                    util::log::message("Read " + std::to_string(length) + " bytes from a socket");
                                    int32_t i = 0;
                                    //in case the unfinished line buffer has stuff
                                    line = util::str::nextLine(buffer, i);
                                    unfinishedLine += line;

                                    if (!firstLineRead)
                                            processFirstLine(unfinishedLine);
                                    else
                                            processHeaderLine(unfinishedLine);

                                    //if it isn't empty then it means we have read a whole line and should clear the buffer
                                    //if it's empty then it means we haven't read a full line
                                    if (line.empty() != 0) unfinishedLine.clear();

                                    //processing the next line
                                    int32_t last = i;
                                    line = util::str::nextLine(buffer, i);
                                    while (i <= length)
                                    {
                                            //this means we have encountered the json file
                                            if (i == length)
                                            {
                                                    //in case we start reading a json mid header reading
                                                    jsonDocByteArr = std::string(buffer.begin() + last, buffer.begin() + i);
                                                    if (jsonDocByteArr.size() == jsonDocSize) {
                                                            _ready = true;
                                                            createJson();
                                                            onFinishedMessage();
                                                    }
                                                    else {
                                                            //TO DO: Make this shi work for smaller buffers
                                                            buffer.resize(jsonDocSize - jsonDocByteArr.size());
                                                            readBody(socket , buffer.size());
                                                    }
                                                    return;
                                            }

                                            processHeaderLine(line);
                                            last = i;
                                            line = util::str::nextLine(buffer, i , length);
                                    }

                                    // in case the buffer stopped mid line
                                    if (line.empty())
                                            unfinishedLine += buffer.substr(i);
                                    //StringHelper::appendToByteArray(unfinishedLine, std::vector<char>(buffer.begin() + i, buffer.end()));
                                    
                                    readHeader(socket);
                            }
                            else
                            {
                                    util::log::error("Error in reading a header: " + ec.message());
                            }
                    });
            }
            void readBody(socketType& socket , size_t l)
            {
                    util::log::info("Called readBody()");
                    //this function is triggered when the buffer is FULL
                    asio::async_read(socket, asio::buffer(buffer.data(), l),
                            [this, &socket](std::error_code ec, std::size_t length) {
                                    if (!ec) {
                                            jsonDocByteArr.append(buffer);
                                            //ConsoleLog::info(jsonDocByteArr);
                                            createJson();
                                            _ready = true;
                                            jsonDocSize = 0;

                                            _canWriteFlag = true;
                                            onFinishedMessage();
                                            util::log::info("Sucessfully read a full message");
                                            buffer.resize(bufferSize);
                                    }
                                    else {
                                            util::log::error("Error in HttpReader , read body: " + ec.message());
                                            _ready = false;
                                            buffer.resize(bufferSize);
                                    }

                            });
            }

            void processHeaderLine(const std::string& buf)
            {
                    for (auto i = 0; i < buf.size(); i++) {
                            if (buf[i] == ':') {
                                    std::string_view header = std::string_view(buf.begin(), buf.begin() + i);
                                    std::string_view value = std::string_view(buf.begin() + i + 1, buf.end());

                                    if (toHeader(header) == Header::CONTENT_LENGTH)
                                            jsonDocSize = std::stoi(value.data());

                                    headers.add(header, value);
                                    return;
                            }
                    }
            }

            bool jsonStarted() const {
                    return line.size() == jsonDocSize;
            }
            void createJson() {
                    doc.SetObject();
                    if (doc.Parse(jsonDocByteArr.data()).HasParseError())
                            util::log::error("Failed to parse json!");
            }
    protected:
            //this is for subclasses. It is called when the read loop is sucessfull in reading a full message
            virtual void onFinishedMessage() = 0;
            virtual void processFirstLine(const std::string& buf) = 0;
    protected:
            HeaderList headers;
            rapidjson::Document doc;
            std::array<std::string, 3> reqTypeStorage;

            std::string unfinishedMessage;
            std::string unfinishedLine;
            std::string buffer;

            //current line being processed. Don't want to realocate it all the time
            std::string line;

            int32_t jsonDocSize = 0;
            std::string jsonDocByteArr;


            int32_t bufferSize;
            bool firstLineRead = false;

            using core::AbstractMessageReader<socketType>::_ready;
            using core::AbstractMessageReader<socketType>::_canWriteFlag;
    };
}

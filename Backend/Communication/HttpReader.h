#pragma once
#include "MessageReader.h"
#include "HttpMessage.h"
#include "StringHelper.h"


class HttpReader : public MessageReader {
public:
	HttpReader() {
		bufferSize = 16;
		buffer.resize(bufferSize);
	}

	bool start(asio::ip::tcp::socket& socket)
	{
		return readHeader(socket);
	}
protected:
	bool readHeader(asio::ip::tcp::socket& socket)
	{
		//I hate how it doesn't approve of std::string as a buffer
		asio::async_read(socket, asio::buffer(buffer.data(), bufferSize),
			[this, &socket](std::error_code ec, std::size_t length) {
				if (!ec) {
					for (int32_t i = 0; i < length; ) {
						//in case the unfinished line buffer has stuff
						line = StringHelper::nextLine(buffer, i);
						StringHelper::appendToByteArray(unfinishedLine, line);

						if (!firstLineRead)
							processFirstLine(unfinishedLine);
						else
							processHeaderLine(unfinishedLine);

						//if it isn't empty then it means we have read a whole line and should clear the buffer
						if (line.empty() != 0) unfinishedLine.clear();

						//processing the next line
						line = StringHelper::nextLine(buffer, i);
						while (!line.empty())
						{
							if (jsonStarted())
							{
								//in case we start reading a json mid header reading
								jsonDocByteArr.insert(jsonDocByteArr.end(), buffer.begin() + i - line.size(), buffer.end());
								jsonDocSize -= (buffer.size() - i - line.size());
								readBody(socket);
								return true;
							}

							processHeaderLine(line);
							line = StringHelper::nextLine(buffer, i);
						}

						// in case the buffer stopped mid line
						if (line.empty())
							StringHelper::appendToByteArray(unfinishedLine, std::vector<char>(buffer.begin() + i, buffer.end()));
						
					}
				}
				else
				{
					ConsoleLog::error("Error in reading a header: " + ec.message());
					return false;
				}
			});

		return false;
	}

	bool readBody(asio::ip::tcp::socket& socket)
	{
		buffer.clear();
		buffer.resize(jsonDocSize);

		asio::async_read(socket, asio::buffer(buffer.data(), bufferSize),
			[this, &socket](std::error_code ec, std::size_t length) {
				if (!ec) {
					doc = std::make_unique<rapidjson::Document>();
					if (doc->Parse(buffer.data()).HasParseError())
						ConsoleLog::error("Failed to parse json!");

					jsonDocSize = 0;
					buffer.clear();
					buffer.resize(bufferSize);

					return true;
				}
				else {
					ConsoleLog::error("Error in HttpReader , read body: " + ec.message());

					return false;
				}
			});

		return false;
	}


	void processHeaderLine(const std::vector<char>& buf)
	{
		for (auto i = 0; i < buf.size(); i++) {
			if (buf[i] == ':') {
				ByteArray header = ByteArray(buf.begin(), buf.begin() + i - 1);
				ByteArray value = ByteArray(buf.begin() + i + 1, buf.end());

				if (HttpCommon::get().stringToHeaderType(header) == HeaderType::CONTENT_LENGTH)
					jsonDocSize = stoi(std::string(value.begin(), value.end()));

				headers.emplace(header, value);
				return;
			}
		}
	}

	bool jsonStarted() const {
		return line[0] == '{';
	}
	virtual void processFirstLine(const std::vector<char>& buf) = 0;
protected:
	std::map<ByteArray, ByteArray> headers;
	std::unique_ptr<rapidjson::Document> doc;
	std::array<std::string, 3> reqTypeStorage;

	ByteArray unfinishedMessage;
	ByteArray unfinishedLine;
	ByteArray buffer;

	//current line being processed. Don't want to realocate it all the time
	ByteArray line;

	int32_t jsonDocSize = 0;
	ByteArray jsonDocByteArr;


	int32_t bufferSize;
	bool firstLineRead = false;
};


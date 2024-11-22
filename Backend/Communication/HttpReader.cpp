#include "HttpReader.h"
#include "StringHelper.h"
#include "ConsoleLog.h"
#include "RequestHeaders.h"

HttpReader::HttpReader() {
	bufferSize = 16;
	buffer.resize(bufferSize);
}

void HttpReader::start(asio::ip::tcp::socket& socket)
{
	readHeader(socket);
}
void HttpReader::readHeader(asio::ip::tcp::socket& socket)
{
	//I hate how it doesn't approve of std::string as a buffer
	asio::async_read(socket, asio::buffer(buffer.data(), bufferSize),
		[this , &socket](std::error_code ec, std::size_t length) {
			if (!ec) {
				for (int32_t i = 0; i < length; ) {
					//in case the unfinished line buffer has stuff
					line = StringHelper::nextLine(buffer , i);
					unfinishedLine.emplace_back(line);

					if (!firstLineRead)
						processFirstLine(unfinishedLine);
					else
						processHeaderLine(unfinishedLine);

					//if it isn't empty then it means we have read a whole line and should clear the buffer
					if (line.empty() != 0) unfinishedLine.clear();

					//processing the next line
					line = StringHelper::nextLine(buffer , i);
					while (!line.empty())
					{
						if (jsonStarted())
						{
							//in case we start reading a json mid header reading
							jsonDocByteArr.emplace_back(buffer.begin() + i - line.size(), buffer.end());
							jsonDocSize -= (buffer.size() - i - line.size());
							readBody(socket);
							return;
						}

						processHeaderLine(line);
						line = StringHelper::nextLine(buffer , i);
					}
					
					// in case the buffer stopped mid line
					if (line.empty())
						unfinishedLine.emplace_back(
							std::vector<char>(buffer.begin() + i , buffer.end())
						);
				}
			}
		});
}

void HttpReader::readBody(asio::ip::tcp::socket& socket)
{
	buffer.clear();
	buffer.resize(jsonDocSize);

	asio::async_read(socket, asio::buffer(buffer.data(), bufferSize),
		[this , &socket](std::error_code ec, std::size_t length) {
			if (!ec) {
				if (doc.Parse(buffer.data()).HasParseError())
					ConsoleLog::error("Failed to parse json!");

				jsonDocSize = 0;
				buffer.clear();
				buffer.resize(bufferSize);
			}
			else {
				ConsoleLog::error("Error in HttpReader , read body: " + ec.message());
			}
		});
}

void HttpReader::processHeaderLine(const std::vector<char>& buf) 
{
	for (auto i = 0; i < buf.size(); i++) {
		if (buf[i] == ':') {
			ByteArray header = ByteArray(buf.begin(), buf.begin() + i - 1);
			ByteArray value = ByteArray(buf.begin() + i + 1, buf.end());

			if (RequestHeaders::get().stringToType(header) == HeaderType::CONTENT_LENGTH)
				jsonDocSize = stoi(std::string(value.begin() , value.end()));

			headers.emplace(header, value);
			return;
		}
	}
}

bool HttpReader::jsonStarted() const {
	return line[0] == '{';
}


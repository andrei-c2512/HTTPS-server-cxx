#include "HttpReader.h"
#include "StringHelper.h"
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
	asio::async_read(socket, asio::buffer(buffer.data(), bufferSize),
		[this](std::error_code ec, std::size_t length) {
			if (!ec) {
				for (int32_t i = 0; i < length; ) {
					//in case the unfinished line buffer has stuff
					std::vector<char> line = StringHelper::nextLine(buffer , i);
					i += line.size();
					unfinishedLine.emplace_back(line);

					processHeaderLine(unfinishedLine);

					if (line.empty() != 0) unfinishedLine.clear();

					//processing the next line
					line = StringHelper::nextLine(buffer , i);
					i += line.size();
					while (line.empty())
					{
						processHeaderLine(line);
						line = StringHelper::nextLine(buffer , i);
						i += line.size();
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
}

void HttpReader::processHeaderLine(const std::vector<char>& buf) {
	for()
}
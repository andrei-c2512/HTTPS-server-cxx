#include "HttpReader.h"
#include "StringHelper.h"
#include "ConsoleLog.h"
#include "HttpCommon.h"

HttpReader::HttpReader() {
	bufferSize = 16;
	buffer.resize(bufferSize);
}

bool HttpReader::start(asio::ip::tcp::socket& socket)
{
	return readHeader(socket);
}
bool HttpReader::readHeader(asio::ip::tcp::socket& socket)
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
							return true;
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
			else
			{
				ConsoleLog::error("Error in reading a header: " + ec.message());
				return false;
			}
		});

	return false;
}

bool HttpReader::readBody(asio::ip::tcp::socket& socket)
{
	buffer.clear();
	buffer.resize(jsonDocSize);

	asio::async_read(socket, asio::buffer(buffer.data(), bufferSize),
		[this , &socket](std::error_code ec, std::size_t length) {
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

void HttpReader::processHeaderLine(const std::vector<char>& buf) 
{
	for (auto i = 0; i < buf.size(); i++) {
		if (buf[i] == ':') {
			ByteArray header = ByteArray(buf.begin(), buf.begin() + i - 1);
			ByteArray value = ByteArray(buf.begin() + i + 1, buf.end());

			if (HttpCommon::get().stringToHeaderType(header) == HeaderType::CONTENT_LENGTH)
				jsonDocSize = stoi(std::string(value.begin() , value.end()));

			headers.emplace(header, value);
			return;
		}
	}
}

bool HttpReader::jsonStarted() const {
	return line[0] == '{';
}

void HttpRequestReader::processFirstLine(const std::vector<char>& buf) {
	int32_t last = 0;
	
	std::vector<ByteArray> vec(3);
	int32_t j = 0 , i = 0;
	for ( i = 0; i < buf.size(); i++) {
		if (buf[i] == ' ') {
			vec[j] = ByteArray(buf.begin() + last, buf.begin() + i - 1);
			last = i + 1;
			j++;
		}
	}
	vec[j] = ByteArray(buf.begin() + last, buf.begin() + i - 1);

	_verb = HttpCommon::get().stringToVerb(std::move(vec[0]));
	_URI = std::move(vec[1]);
	_version = std::move(vec[2]);
}

std::unique_ptr<HttpRequest> HttpRequestReader::request() const {
	return std::make_unique<HttpRequest>(_verb, _URI, _version, headers, std::move(doc));
}

ByteArray HttpRequestReader::version() const noexcept { return _version; }
ByteArray HttpRequestReader::URI() const noexcept { return _URI; }
HttpVerb HttpRequestReader::verb() const noexcept { return _verb; }

void HttpResponseReader::processFirstLine(const std::vector<char>& buf) {
	int32_t last = 0;

	std::vector<ByteArray> vec(3);
	int32_t j = 0 , i = 0;
	for (; i < buf.size(); i++) {
		if (buf[i] == ' ') {
			vec[j] = ByteArray(buf.begin() + last, buf.begin() + i - 1);
			last = i + 1;
			j++;
		}
	}
	vec[j] = ByteArray(buf.begin() + last, buf.begin() + i - 1);

	_version = std::move(vec[0]);
	_statusCode = StringHelper::toString(std::move(vec[1]));
	_phrase = std::move(vec[2]);
}

ByteArray HttpResponseReader::version() const noexcept { return _version; }
int16_t HttpResponseReader::statusCode() const noexcept { return _statusCode; }
ByteArray HttpResponseReader::phrase() const noexcept { return _phrase; }
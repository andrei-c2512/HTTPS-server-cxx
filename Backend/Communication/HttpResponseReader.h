#pragma once
#include "HttpReader.h"
#include "HttpResponse.h"


class HttpResponseReader : public HttpReader {
public:
	HttpResponseReader() = default;


	HttpVersion version() const noexcept { return _version; }
	int16_t statusCode() const noexcept { return _statusCode; }
	ByteArray phrase() const noexcept { return _phrase; }

	std::unique_ptr<HttpResponse> response() {
		return std::make_unique<HttpResponse>(_version, _statusCode, _phrase, headers, std::move(doc));
		//return nullptr;
	}

	ByteArray messageByteArray() const {

	}
	std::string messageString() const {

	}
protected:
	void processFirstLine(const std::vector<char>& buf) override {
		int32_t last = 0;

		std::vector<ByteArray> vec(3);
		int32_t j = 0, i = 0;
		for (; i < buf.size(); i++) {
			if (buf[i] == ' ') {
				vec[j] = ByteArray(buf.begin() + last, buf.begin() + i - 1);
				last = i + 1;
				j++;
			}
		}
		vec[j] = ByteArray(buf.begin() + last, buf.begin() + i - 1);

		_version = HttpCommon::get().stringToVersion(std::move(vec[0]));
		_statusCode = StringHelper::toString(std::move(vec[1]));
		_phrase = std::move(vec[2]);
	}
protected:
	HttpVersion _version;
	int16_t _statusCode;
	ByteArray _phrase;
};


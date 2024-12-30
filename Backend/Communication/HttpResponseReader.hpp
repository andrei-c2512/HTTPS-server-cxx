#pragma once
#include "HttpReader.hpp"
#include "HttpResponse.hpp"
#include "TsQueue.hpp"

template<IsSocket socketType>
class HttpResponseReader : public HttpReader<socketType> {
public:
	HttpResponseReader(bool& canWriteFlag ,TsQueue<std::shared_ptr<HttpResponse>>& queue0) 
		:HttpReader<socketType>(canWriteFlag), queue(queue0)
	{}
	HttpCommon::Version version() const noexcept { return _version; }
	int16_t statusCode() const noexcept { return _statusCode; }
	std::string phrase() const noexcept { return _phrase; }

	std::unique_ptr<HttpResponse> response() {
		return std::make_unique<HttpResponse>(_version, _statusCode, _phrase, headers, std::move(doc) , _userId);
	}

	std::string messageString() const {
		return "";
	}
protected:
	void onFinishedMessage() override {
		assert(_ready && "Attempted to call onFinishedMessage when the message wasn't finished");
		_ready = false;
		queue.push_back(response());
	}
	void processFirstLine(const std::string& buf) override {
		int32_t last = 0;

		std::vector<std::string> vec(3);
		int32_t j = 0, i = 0;
		for (; i < buf.size(); i++) {
			if (buf[i] == ' ') {
				vec[j] = std::string(buf.begin() + last, buf.begin() + i);
				last = i + 1;
				j++;
			}
		}
		vec[j] = std::string(buf.begin() + last, buf.begin() + i);

		_version = HttpCommon::VersionCodex::get().stringToVersion(std::move(vec[0]));
		_statusCode = stoi(std::move(vec[1]));
		_phrase = std::move(vec[2]);
	}
protected:
	HttpCommon::Version _version;
	int16_t _statusCode;
	std::string _phrase;

	TsQueue<std::shared_ptr<HttpResponse>>& queue;

	using HttpReader<socketType>::_ready;
	using HttpReader<socketType>::doc;
	using HttpReader<socketType>::headers;
	using HttpReader<socketType>::_userId;
};


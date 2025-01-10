#pragma once
#include "HttpReader.hpp"
#include "HttpRequest.hpp"


template<IsSocket socketType>
class HttpRequestReader : public HttpReader<socketType> {
public:
	HttpRequestReader(bool& canWriteFlag , TsQueue<std::shared_ptr<HttpRequest>>& queue0)
		:HttpReader<socketType>(canWriteFlag) , queue(queue0)
	{}

	std::shared_ptr<HttpRequest> request()  {
		return std::make_shared<HttpRequest>(_verb, _URI, _version, headers, std::move(doc) , _userId);
	}


	HttpCommon::Version version() const noexcept { return _version; }
	std::string URI() const noexcept { return _URI; }
	HttpCommon::Verb verb() const noexcept { return _verb; }

	
	std::string messageString() const {
		std::string m;
		m.append(HttpRequest::requestFirstLine(_verb, _URI, _version));
		m.append(HttpHeaders::headersToString(headers));
		m.append(HttpMessage::documentToString(doc));

		return m;
	}


	/*
	*/
	using HttpReader<socketType>::start;
	/*
	*/
protected:
	void onFinishedMessage() override {
		assert(_ready && "Attempted to call onFinishedMessage when the message wasn't finished");
		_ready = false;
		queue.push_back(request());
	}
	void processFirstLine(const std::string& buf) override {
		int32_t last = 0;

		std::vector<std::string_view> vec(3);
		int32_t j = 0, i = 0;
		for (i = 0; i < buf.size(); i++) {
			if (buf[i] == ' ') {
				vec[j] = std::string_view(buf.begin() + last, buf.begin() + i);
				last = i + 1;
				j++;
			}
		}
		vec[j] = std::string(buf.begin() + last, buf.begin() + i);

		_verb = HttpCommon::toVerb(std::move(vec[0]));
		_URI = std::move(vec[1]);
		_version = HttpCommon::toVersion(std::move(vec[2]));
	}
protected:
	HttpCommon::Verb _verb;
	std::string _URI;
	HttpCommon::Version _version;
	TsQueue<std::shared_ptr<HttpRequest>>& queue;

	using HttpReader<socketType>::doc;
	using HttpReader<socketType>::headers;
	using HttpReader<socketType>::_ready;
	using HttpReader<socketType>::_userId;
};

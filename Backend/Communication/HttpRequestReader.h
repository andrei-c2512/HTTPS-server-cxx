#pragma once
#include "HttpReader.h"
#include "HttpRequest.h"


class HttpRequestReader : public HttpReader {
public:
	HttpRequestReader() = default;


	std::unique_ptr<HttpRequest> request()  {
		return std::make_unique<HttpRequest>(_verb, _URI, _version, headers, std::move(doc));
	}


	HttpVersion version() const noexcept { return _version; }
	ByteArray URI() const noexcept { return _URI; }
	HttpVerb verb() const noexcept { return _verb; }

	ByteArray messageByteArray() const {
		ByteArray m;
		HttpCommon& common = HttpCommon::get();

		ByteArray verbArr = common.verbToString(_verb);
		ByteArray versionArr = common.versionToString(_version);

		ByteArray space;
		space.emplace_back(' ');

		//for the first line
		StringHelper::appendToByteArray(m, verbArr);
		StringHelper::appendToByteArray(m, space);
		StringHelper::appendToByteArray(m, _URI);
		StringHelper::appendToByteArray(m, space);
		StringHelper::appendToByteArray(m, versionArr);
		//the rest
		ByteArray head = HttpCommon::headersToByteArray(headers);
		ByteArray body = HttpCommon::documentToByteArray(*doc);
		//putting it all together
		StringHelper::appendToByteArray(m, head);
		StringHelper::appendToByteArray(m, body);
		return m;
	}
	std::string messageString() const {
		std::string m;
		HttpCommon& common = HttpCommon::get();

		m = std::string(common.verbToString(_verb).data());
		m.append(" ");
		m.append(std::string(_URI.data()));
		m.append(" ");
		m.append(common.versionToString(_version).data());
		m.append("\n");

		m.append(HttpCommon::headersToString(headers));
		m.append(HttpCommon::documentToString(*doc));

		return m;
	}
protected:
	void processFirstLine(const std::vector<char>& buf) override {
		int32_t last = 0;

		std::vector<ByteArray> vec(3);
		int32_t j = 0, i = 0;
		for (i = 0; i < buf.size(); i++) {
			if (buf[i] == ' ') {
				vec[j] = ByteArray(buf.begin() + last, buf.begin() + i - 1);
				last = i + 1;
				j++;
			}
		}
		vec[j] = ByteArray(buf.begin() + last, buf.begin() + i - 1);

		_verb = HttpCommon::get().stringToVerb(std::move(vec[0]));
		_URI = std::move(vec[1]);
		_version = HttpCommon::get().stringToVersion(std::move(vec[2]));
	}
protected:
	HttpVerb _verb;
	ByteArray _URI;
	HttpVersion _version;

	bool ready = false;
};

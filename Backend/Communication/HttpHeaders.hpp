#pragma once
#include "HttpCommon.hpp"


class HttpHeaders {
public:
	HttpHeaders() 
	{}

	void add(const std::string_view key, const std::string_view val) {
		auto header = HttpCommon::toHeader(key);
		if (header != HttpCommon::Header::INVALID) {
			_supportedMap.emplace(header, val.data());
		}
		else {
			_unsupportedMap.emplace(key, val.data());
		}
	}
	void add(HttpCommon::Header header, const std::string& val) {
		_supportedMap.emplace(header, val);
	}
	//returns a map of the headers that are currently supported
	const std::map<HttpCommon::Header, std::string>& supportedMap() const {
		return _supportedMap;
	}
	//returns a map of the headers that are not supported
	const std::map<std::string, std::string>& unsupportedMap() const {
		return _unsupportedMap;
	}
	static std::string headersToString(const HttpHeaders& headers) {
		ConsoleLog::warning("Headers may not be shown in the way they were sent because the function shows" 
			"supported headers first and then the unsupported headers");

		const std::map<HttpCommon::Header, std::string>& supportedMap = headers.supportedMap();
		const auto& unsupportedMap = headers.unsupportedMap();

		std::string headerText;
		headerText.reserve(avgLineLength * (supportedMap.size() + unsupportedMap.size()));

		std::string line;
		line.reserve(avgLineLength);
		for (const auto& [key, value] : supportedMap) {
			std::string keyStr = HttpCommon::headerArr[(int)key].data();
			line.append(keyStr);
			line.append(":");
			line.append(value);
			line.append("\n");

			headerText.append(line);
			line.clear();
		}

		for (const auto& [key, value] : unsupportedMap) {
			line.append(key);
			line.append(":");
			line.append(value);
			line.append("\n");

			headerText.append(line);
			line.clear();
		}


		return headerText;
	}
private:
	static constexpr int32_t avgLineLength = 40;
	std::map<HttpCommon::Header, std::string> _supportedMap;
	std::map<std::string, std::string> _unsupportedMap;
};
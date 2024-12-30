#pragma once
#include "HttpCommon.hpp"


class HttpHeaders {
public:
	HttpHeaders() = default;

	void add(const std::string& key, const std::string& val) {
		_map.emplace(HttpCommon::HeaderCodex::get().stringToHeader(key), val);
	}
	void add(HttpCommon::Header header, const std::string& val) {
		_map.emplace(header, val);
	}

	const std::map<HttpCommon::Header, std::string>& map() const {
		return _map;
	}
	static std::string headersToString(const HttpHeaders& headers) {
		std::string headerText;
		const std::map<HttpCommon::Header, std::string>& map = headers.map();

		std::string line;
		line.reserve(avgLineLength);
		for (const auto& [key, value] : map) {
			std::string keyStr = HttpCommon::HeaderCodex::get().headerToString(key);
			line.append(keyStr.begin(), keyStr.end());
			line.append(":");
			line.append(value.begin(), value.end());
			line.append("\n");

			headerText.append(line);
		}

		return headerText;
	}
private:
	static constexpr int32_t avgLineLength = 40;
	std::map<HttpCommon::Header, std::string> _map;
};
#pragma once
#include "HttpCommon.h"


class HttpHeaders {
public:
	HttpHeaders() = default;

	void add(const std::string& key, const std::string& val) {
		_map.emplace(key, val);
	}
	void add(HttpCommon::Header header, const std::string& val) {
		_map.emplace(HttpCommon::HeaderCodex::get().headerToString(header), val);
	}

	const std::map<std::string, std::string>& map() const {
		return _map;
	}
	static std::string headersToString(const HttpHeaders& headers) {
		std::string headerText;
		const std::map<std::string, std::string>& map = headers.map();

		for (const auto& [key, value] : map) {
			std::string line;
			line.append(key.begin(), key.end());
			line.append(":");
			line.append(value.begin(), value.end());
			line.append("\n");

			headerText.append(line);
		}

		return headerText;
	}
private:
	std::map<std::string, std::string> _map;
};
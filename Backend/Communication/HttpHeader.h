#pragma once
#include "HttpCommon.h"


class HttpHeader {
public:
	HttpHeader() = default;

	void add(const std::string& key, const std::string& val) {
		_map.emplace(key, val);
	}
	void add(HttpCommon::Header header, const std::string& val) {
		_map.emplace(HttpCommon::HeaderCodex::get().headerToString(header), val);
	}

	const std::map<std::string, std::string>& map() const {
		return _map;
	}
private:
	std::map<std::string, std::string> _map;
};
#pragma once
#include "Common.hpp"

namespace ResourceHandling::Utility {
	constexpr const char* registerFields[3] = { "name" , "email" , "password" };
	inline const char* hostName = "localhost";
	inline bool extractFieldValue(const char** dest, const rapidjson::Document& body, const char* field) {
		if (body.HasMember(field) && body[field].IsString()) {
			*dest = body[field].GetString();
			return true;
		}
		else
			return false;
	}
}
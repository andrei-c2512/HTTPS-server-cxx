#pragma once
// depends on rapidjson and OpenSSL
#include "Common.hpp"
#include "openssl/bio.h"

//called the class like this because OpenSSl seems to call transformations 'filters' , with their BIO things

namespace util::filter{
	std::string encodeBase64(const std::string& data);
	std::string encodeBase64(rapidjson::Document doc);
	std::string decodeBase64(const std::string& encodedData);
}

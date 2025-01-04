#pragma once
#include "HttpCommon.hpp"
#include "HttpHeaders.hpp"


//this class is for filtering bad formated/incomplete/bs requests and responses
class HttpFilter {
public:
	HttpFilter()
		:ctCodex(HttpCommon::ContentTypeCodex::get())
	{}
	//returns the status code associated with the error that occurs. If there isn't any , then it return 100
	[[nodiscard]] std::pair<HttpCommon::StatusCode, std::string> filter(const HttpHeaders& headers) {
		std::pair<HttpCommon::StatusCode, std::string> result = validResponse;

		if (contentFilterEnabled) {
			result = contentTypeFilter(headers);
		}


		//I arranged this in a pretty interesting way. So if the message does in fact contain a JWT , it will be returned ,
		// along with the OK status code
		if (jwtFilterEnabled) {
			result = jwtFilter(headers);

			if (result.first != HttpCommon::StatusCode::CONTINUE)
				return result;
		}

		return result;
	}
	void enableJWTFilter(bool state) {
		jwtFilterEnabled = state;
	}
	void enableContentFilter(bool state, HttpCommon::ContentType type) {
		contentFilterEnabled = state;
		contentType = type;
	}
private:
	std::pair<HttpCommon::StatusCode, std::string> jwtFilter(const HttpHeaders& headers) {
		const auto& map = headers.supportedMap();
		auto it = map.find(HttpCommon::Header::AUTHORIZATION);
		if (it == map.end())
			return std::make_pair(HttpCommon::StatusCode::UNAUTHORIZED , "Did not find authorization header");
		else
		{
			size_t keyword1 = it->second.find(authKeyword1);
			if (keyword1 == std::string::npos)
				return std::make_pair(HttpCommon::StatusCode::BAD_REQUEST, "Invalid authorization data");
			else {
				return std::make_pair(HttpCommon::StatusCode::CONTINUE, it->second.substr(keyword1 + strlen(authKeyword1)));
			}
		}
	}
	std::pair<HttpCommon::StatusCode, std::string> contentTypeFilter(const HttpHeaders& headers) {
		const auto& map = headers.supportedMap();
		auto it = map.find(HttpCommon::Header::CONTENT_TYPE);
		if (it == map.end())
			return std::make_pair(HttpCommon::StatusCode::BAD_REQUEST , "Did not find content type header");
		else {
			//mapping the extracted type to the content type
			auto contentTypeMapIt = ctCodex.stringToType(it->second);
			if (contentTypeMapIt == ctCodex.map.end()) {
				return std::make_pair(HttpCommon::StatusCode::BAD_REQUEST,
					"Invalid/badly formatted content type header. Available formats: " + ctCodex.availableFormatsString());
			}
			else if(contentTypeMapIt->second != contentType){
				return std::make_pair(HttpCommon::StatusCode::BAD_REQUEST,
					"Incorrect format");
			}
			else {
				return validResponse;
			}

		}
	}
private:
	static constexpr auto authKeyword1 = "Bearer ";
 	static constexpr auto validResponse = std::make_pair(HttpCommon::StatusCode::CONTINUE, "OK");

	bool jwtFilterEnabled = false;

	bool contentFilterEnabled = false;
	HttpCommon::ContentType contentType = HttpCommon::ContentType::JSON;

	HttpCommon::ContentTypeCodex& ctCodex;
};
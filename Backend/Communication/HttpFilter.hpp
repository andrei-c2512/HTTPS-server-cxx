#pragma once
#include "HttpCommon.hpp"
#include "HttpHeaders.hpp"


//this class is for filtering bad formated/incomplete/bs requests and responses
class HttpFilter {
public:
	//returns the status code associated with the error that occurs. If there isn't any , then it return 100
	HttpCommon::StatusCode filter(const HttpHeaders& headers) {

	}
	void enableJWTFilter(bool state) {

	}
	void enableContentFilter(bool state, HttpCommon::ContentType type) {

	}
private:
	HttpCommon::StatusCode jwtFilter(const HttpHeaders& headers) {
		const auto& map = headers.map();
		auto it = map.find(HttpCommon::Header::CONTENT_TYPE);
		if (it == map.end())
			return HttpCommon::StatusCode::CLIENT_ERROR;
		else
		{

		}
	}
private:

};
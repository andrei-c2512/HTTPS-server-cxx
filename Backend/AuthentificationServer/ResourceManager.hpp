#pragma once
#include "HttpResponse.hpp"
#include "HttpRequest.hpp"
#include "HandlingContext.hpp"
//I would've made this a class but it would've just retained some static functions so that I can point to them

namespace ResourceManager {
	typedef std::shared_ptr<HttpResponse> ResponsePtr;
	typedef std::shared_ptr<HttpRequest> RequestPtr;

	namespace Aux {
		bool assignFieldValue(const char** dest, const rapidjson::Document& body, const char* field);
	}

	extern HandlingContext ctx;
	extern const char* hostName;
	namespace Dash {
		ResponsePtr GET_dash(RequestPtr request);
	}
	namespace Auth {
		extern const char* registerFields[3];
		ResponsePtr GET_register(RequestPtr req);
		ResponsePtr POST_register(RequestPtr request);
	}
}
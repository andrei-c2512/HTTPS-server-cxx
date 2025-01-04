#include "ResourceManager.hpp"

ResourceManager::ResponsePtr ResourceManager::Auth::POST_register(RequestPtr request) 
{
	const rapidjson::Document& body = request->document();
	const char* fieldValues[3];

	if (!Aux::assignFieldValue(&fieldValues[0], body, registerFields[0])) {
		return HttpResponse::createErrorResponse("Name is invalid or could not find field");
	}

	//we check if name is taken before reading the other fields , because we don't want to do operations
	//on a bad request
	if (ctx.dbHandler->isNameTaken(fieldValues[0]))
		return HttpResponse::createErrorResponse("Name already taken");

	for (int8_t i = 1; i < 3; i++) {
		if (!Aux::assignFieldValue(&fieldValues[i], body, registerFields[i])) {
			return HttpResponse::createErrorResponse("Field is missing/invalid");
		}
	}

	//need to hash again here kk
	ctx.dbHandler->addUser(fieldValues[0], fieldValues[1], fieldValues[2]);

	ctx.jwtGenerator->setPayload(
		StringHelper::createBasicDoc(std::make_pair("name", fieldValues[0]))
	);


	rapidjson::Document jwtResponseBody = ctx.jwtGenerator->sucessfulJwtBody();
	rapidjson::StringBuffer buf;
	rapidjson::Writer w(buf);
	jwtResponseBody.Accept(w);


	HttpHeaders headers;
	headers.add(HttpCommon::Header::CONTENT_TYPE, "json");
	headers.add(HttpCommon::Header::CONTENT_LENGTH, std::to_string(buf.GetSize()));
	headers.add(HttpCommon::Header::HOST, hostName);

	return std::make_unique<HttpResponse>(200, "OK", std::move(headers), std::move(jwtResponseBody));
}

ResourceManager::ResponsePtr ResourceManager::Auth::GET_register(RequestPtr req) {
	return nullptr;
}
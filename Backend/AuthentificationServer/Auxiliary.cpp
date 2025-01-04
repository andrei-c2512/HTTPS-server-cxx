#include "ResourceManager.hpp"


bool ResourceManager::Aux::assignFieldValue(const char** dest, const rapidjson::Document& body, const char* field) {
	if (body.HasMember(field) && body[field].IsString()) {
		*dest = body[field].GetString();
		return true;
	}
	else
		return false;
}

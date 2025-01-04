#pragma once
#include "JWTgenerator.hpp"
#include "JWTvalidator.hpp"
#include "DatabaseHandler.hpp"
#include "WebPageDeliverer.hpp"

struct HandlingContext {
	JWT::Generator* jwtGenerator = nullptr;
	JWT::Validator* jwtValidator = nullptr;
	DatabaseHandler* dbHandler = nullptr;
	WebDelivery::PageDeliverer* wpDeliverer = nullptr;
};

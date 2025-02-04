#pragma once
#include "ResourceHandler.hpp"
#include "ResourceHandlingUtility.hpp"
#include "HandlingContext.hpp"

namespace ResourceHandling {
	class RegisterResource : public ResourceHandler {
	public:
		RegisterResource(BaseHandlingContext* ctx)
			:ResourceHandler(ctx)
		{
			update();
		}
	protected:
		HttpHandler GET_handler() const noexcept override {
			auto handler = []([[maybe_unused]] RequestPtr req, [[maybe_unused]] BaseHandlingContext* ctx) -> ResponsePtr {
				return HttpResponse::createErrorResponse("Unavailable yet");
				};
			return static_cast<HttpHandler>(handler);
		}
		HttpHandler POST_handler() const noexcept override {
			auto handler = [](RequestPtr request, BaseHandlingContext* context) -> ResponsePtr {
				HandlingContext* ctx = static_cast<HandlingContext*>(context);

				const rapidjson::Document& body = request->document();
				const char* fieldValues[3];

				if (!Utility::extractFieldValue(&fieldValues[0], body, Utility::registerFields[0])) {
					return HttpResponse::createErrorResponse("Name is invalid or could not find field");
				}

				//we check if name is taken before reading the other fields , because we don't want to do operations
				//on a bad request
				if (ctx->dbHandler().isNameTaken(fieldValues[0]))
					return HttpResponse::createErrorResponse("Name already taken");

				for (int8_t i = 1; i < 3; i++) {
					if (!Utility::extractFieldValue(&fieldValues[i], body, Utility::registerFields[i])) {
						return HttpResponse::createErrorResponse("Field is missing/invalid");
					}
				}

				//need to hash again here kk
				ctx->dbHandler().addUser(fieldValues[0], fieldValues[1], fieldValues[2]);

				ctx->jwtGenerator().setPayload(
					StringHelper::createBasicDoc(std::make_pair("name", fieldValues[0]))
				);


				rapidjson::Document jwtResponseBody = ctx->jwtGenerator().sucessfulJwtBody();
				rapidjson::StringBuffer buf;
				rapidjson::Writer w(buf);
				jwtResponseBody.Accept(w);


				HttpHeaders headers;
				headers.add(HttpCommon::Header::CONTENT_TYPE, "json");
				headers.add(HttpCommon::Header::CONTENT_LENGTH, std::to_string(buf.GetSize()));
				headers.add(HttpCommon::Header::HOST, Utility::hostName);

				return std::make_unique<HttpResponse>(200, "OK", std::move(headers), std::move(jwtResponseBody));
				};
			return static_cast<HttpHandler>(handler);
		}
	};
}
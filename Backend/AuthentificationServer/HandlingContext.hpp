#pragma once
#include "JWTgenerator.hpp"
#include "JWTvalidator.hpp"
#include "DatabaseHandler.hpp"
#include "WebPageDeliverer.hpp"
#include "BaseHandlingContext.hpp"


namespace ResourceHandling {
	class HandlingContext : public BaseHandlingContext {
		// So I decided to use the builder pattern because a) doesn't make sense for any of them to have copy assignment
		//												   b) move semantics don't work either because postgres library shits itself 
		//													  when it tries to connect if I use move on it
		//                                                 c) the constructor would have too many arguments
	public:
		HandlingContext() = default;

		void makeJwtContext(const std::string& privateKeyFile, const std::string& publicKeyFile) noexcept;
		void makeWebDeliverer(const std::string& storageFolder , const std::string& webFileFolder) noexcept;
		void makeDbHandler(const std::string& localHost, int16_t port, const std::string& dbName,
			const std::string& user, const std::string& password) noexcept;

		JWT::Generator& jwtGenerator() const noexcept;
		JWT::Validator& jwtValidator() const noexcept;

		WebDelivery::PageDeliverer& pageDeliverer() const noexcept;
		DatabaseHandler& dbHandler() const noexcept;
	private:
		std::unique_ptr<JWT::Generator> _jwtGenerator = nullptr;
		std::unique_ptr<JWT::Validator> _jwtValidator = nullptr;
		std::unique_ptr<DatabaseHandler> _dbHandler = nullptr;
		std::unique_ptr<WebDelivery::PageDeliverer> _wpDeliverer = nullptr;
	};
}
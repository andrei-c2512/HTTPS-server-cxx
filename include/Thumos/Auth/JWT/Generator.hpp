#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Utility/Utility.hpp"
#include "openssl/hmac.h"
#include "openssl/rsa.h"
#include "openssl/evp.h"
#include "openssl/pem.h"
#include <cstdio>

namespace thm::jwt{
	class Generator {
	public:
		Generator(const std::string& privateKeyPath);
		~Generator();
		Generator(const Generator& gen) = delete;
		Generator& operator=(const Generator& gen) = delete;
		Generator(Generator&& gen) noexcept;
		Generator& operator=(Generator&& gen);
		static rapidjson::Document createHeader();
		void setPayload(rapidjson::Document payload0);
		std::string createJWT();
		rapidjson::Document sucessfulJwtBody();
	private:
		std::string createSignature(const std::string& plainText);
		void handleEVPError(int errorCode, const std::string_view& message);
	private:
		rapidjson::Document payloadDoc;
		EVP_PKEY* privateKey = nullptr;
		EVP_MD_CTX* context = nullptr;
	};
}

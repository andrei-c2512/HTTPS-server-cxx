#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "DataFilters.h"
#include "StringHelper.h"
#include "openssl/hmac.h"
#include "openssl/rsa.h"
#include "openssl/evp.h"


class JWTgenerator {
public:
	JWTgenerator(const std::string& privateKeyPath) {
		FILE* privateKeyFile = nullptr;
		fopen_s(&privateKeyFile, privateKeyPath.c_str(), "r");
		context = EVP_MD_CTX_new();
		privateKey = PEM_read_PrivateKey(privateKeyFile, nullptr, nullptr, nullptr);

		fclose(privateKeyFile);
	}
	~JWTgenerator() {
		if(privateKey)
			EVP_PKEY_free(privateKey);
		if (context)
			EVP_MD_CTX_free(context);
	}
	static rapidjson::Document createHeader() {
		rapidjson::Document header;
		header["alg"] = "HS256";
		header["typ"] = "JWT";

		return header;
	}
	void setPayload(std::unique_ptr<rapidjson::Document> payload0) {
		payloadDoc = std::move(payload0);
	}
	std::string createJWT(const std::string key) {
		std::string plainText =  
			DataFilters::encodeBase64(StringHelper::jsonToString(createHeader())) + 
			'.' + 
			DataFilters::encodeBase64(StringHelper::jsonToString(*payloadDoc));

		return plainText + "." + createSignature(plainText);
	}
private:
	std::string createSignature(const std::string& plainText) {
		uint8_t signature[256];
		size_t signatureLen;

		int errorCode;
		errorCode = EVP_DigestSignInit(context, nullptr, EVP_sha256(), nullptr, privateKey);
		handleEVPError(errorCode, "Failed to initialize evp for JWT");
		errorCode = EVP_DigestSignUpdate(context, plainText.c_str(), plainText.size());
		handleEVPError(errorCode, "Failed to update evp for JWT");
		errorCode = EVP_DigestSignFinal(context, signature, &signatureLen);
		handleEVPError(errorCode, "Failed to finalize evp for JWT");

		return DataFilters::encodeBase64(
			std::string(reinterpret_cast<const char*>(signature), signatureLen));
	}
private:
	void handleEVPError(int errorCode , const std::string_view& message) {
		if (errorCode != 1) {
			ConsoleLog::error(message);
		}
	}
private:
	std::unique_ptr<rapidjson::Document> payloadDoc;
	EVP_PKEY* privateKey = nullptr;
	EVP_MD_CTX* context = nullptr;
};
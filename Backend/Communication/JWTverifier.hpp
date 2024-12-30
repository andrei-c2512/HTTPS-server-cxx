#pragma once
#include "DataFilters.hpp"
#include "openssl/evp.h"

namespace JWT{
	class Verifier {
	public:
		Verifier(const std::string_view& publicKeyPath) {
			FILE* file = nullptr;
			fopen_s(&file, publicKeyPath.data(), "r");
			context = EVP_MD_CTX_new();
			publicKey = PEM_read_PUBKEY(file, nullptr, nullptr, nullptr);
			fclose(file);
		}
		Verifier() {
			if (publicKey)
				EVP_PKEY_free(publicKey);
		}
		void setJWT(const std::string_view& jwt0) {
			jwt = jwt0;
		}
		bool verrify() {
			//basically search for . after the first . position
			size_t secondDotPos = jwt.find('.', (jwt.find('.') + 1));
			std::string_view plainText = jwt.substr(0, secondDotPos);
			//+1 to avoid the dot
			std::string_view signature = jwt.substr(secondDotPos + 1);

			EVP_DigestVerifyInit(context, nullptr, EVP_sha256(), nullptr, publicKey);
			EVP_DigestVerifyUpdate(context, (const unsigned char*)plainText.data(), plainText.size());

			return EVP_DigestVerifyFinal(context, (const unsigned char*)signature.data(), signature.size());
		}
	private:
		std::string_view getPlainText() {
			std::array<std::string_view, 3> parts;
			size_t last = 0;
			int8_t i;
			for (i = 0; i < 2; i++) {
				size_t cur = jwt.find('.');
				parts[i] = jwt.substr(last, cur - last);
				last = cur;
			}
			parts[i] = jwt.substr(last, jwt.size() - last);
		}
	private:
		EVP_MD_CTX* context = nullptr;
		EVP_PKEY* publicKey = nullptr;
		std::string_view jwt;
	};
}
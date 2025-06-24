#pragma once
#include "Utility/Utility.hpp"
#include "openssl/evp.h"
#include "openssl/pem.h"

namespace thm::jwt{
	class Validator {
	public:
		Validator(const std::string_view& publicKeyPath);
		~Validator();
		Validator(const Validator& val) = delete;
		Validator& operator=(const Validator& val) = delete;
		Validator(Validator&& val);
		Validator& operator=(Validator&& val);
		void setJWT(const std::string_view& jwt0);
		bool validate();
	private:
		std::string_view getPlainText();
	private:
		EVP_MD_CTX* context = nullptr;
		EVP_PKEY* publicKey = nullptr;
		std::string_view jwt;
	};
}

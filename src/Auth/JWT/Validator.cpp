#include "Thumos/Auth/JWT/Validator.hpp"

namespace thm::jwt{
        Validator::Validator(const std::string_view& publicKeyPath) {
                FILE* file = fopen(publicKeyPath.data(), "r");
                context = EVP_MD_CTX_new();
                publicKey = PEM_read_PUBKEY(file, nullptr, nullptr, nullptr);
                fclose(file);
        }
        Validator::~Validator() {
                if (publicKey)
                        EVP_PKEY_free(publicKey);
                if(context)
                        EVP_MD_CTX_free(context);
        }
        Validator::Validator(Validator&& val) {
                publicKey = val.publicKey;
                context = val.context;
                val.publicKey = nullptr;
                val.context = nullptr;
        }
        Validator& Validator::operator=(Validator&& val) {
                publicKey = val.publicKey;
                context = val.context;
                val.publicKey = nullptr;
                val.context = nullptr;
                return *this;
        }
        void Validator::setJWT(const std::string_view& jwt0) {
                jwt = jwt0;
        }
        bool Validator::validate() {
                //basically search for . after the first . position
                size_t secondDotPos = jwt.find('.', (jwt.find('.') + 1));
                std::string_view plainText = jwt.substr(0, secondDotPos);
                //+1 to avoid the dot
                std::string_view signature = jwt.substr(secondDotPos + 1);

                EVP_DigestVerifyInit(context, nullptr, EVP_sha256(), nullptr, publicKey);
                EVP_DigestVerifyUpdate(context, (const unsigned char*)plainText.data(), plainText.size());

                return EVP_DigestVerifyFinal(context, (const unsigned char*)signature.data(), signature.size());
        }
        std::string_view Validator::getPlainText() {
                std::array<std::string_view, 3> parts;
                size_t last = 0;
                int8_t i;
                for (i = 0; i < 2; i++) {
                        size_t cur = jwt.find('.');
                        if(cur == std::string::npos){
                            return "";
                        }
                        parts[i] = jwt.substr(last, cur - last);
                        last = cur;
                }
                parts[i] = jwt.substr(last, jwt.size() - last);
                
                return parts[1]; 
        }
}

#include "Thumos/Auth/JWT/Generator.hpp"

namespace thm::jwt {
        Generator::Generator(const std::string& privateKeyPath) {
                FILE* privateKeyFile = fopen(privateKeyPath.c_str(), "r");
                context = EVP_MD_CTX_new();
                privateKey = PEM_read_PrivateKey(privateKeyFile, nullptr, nullptr, nullptr);

                fclose(privateKeyFile);
        }
        Generator::~Generator() {
                if (privateKey)
                        EVP_PKEY_free(privateKey);
                if (context)
                        EVP_MD_CTX_free(context);
        }
        Generator::Generator(Generator&& gen) noexcept {
                privateKey = gen.privateKey;
                context = gen.context;
                gen.privateKey = nullptr;
                gen.context = nullptr;
        }
        Generator& Generator::operator=(Generator&& gen) {
                privateKey = gen.privateKey;
                context = gen.context;
                gen.privateKey = nullptr;
                gen.context = nullptr;
                return *this;
        }

        rapidjson::Document Generator::createHeader() {
                rapidjson::Document header;
                header.SetObject();
                util::str::addPair(header, std::make_pair("alg", "HS256"));
                util::str::addPair(header, std::make_pair("typ", "JWT"));

                return header;
        }

        void Generator::setPayload(rapidjson::Document payload0) {
                payloadDoc = std::move(payload0);
        }
        std::string Generator::createJWT() {
                std::string plainText =
                        util::filter::encodeBase64(util::str::jsonToString(createHeader())) +
                        '.' +
                        util::filter::encodeBase64(util::str::jsonToString(payloadDoc));

                return plainText + "." + createSignature(plainText);
        }
        rapidjson::Document Generator::sucessfulJwtBody() {
                return util::str::createBasicDoc(std::make_pair("token", (const char*)createJWT().data()),
                                                                                        std::make_pair("message", "Sign in sucessfull"));
        }
        std::string Generator::createSignature(const std::string& plainText) {
                uint8_t signature[256];
                size_t signatureLen;

                int errorCode;
                errorCode = EVP_DigestSignInit(context, nullptr, EVP_sha256(), nullptr, privateKey);
                handleEVPError(errorCode, "Failed to initialize evp for JWT");
                errorCode = EVP_DigestSignUpdate(context, plainText.c_str(), plainText.size());
                handleEVPError(errorCode, "Failed to update evp for JWT");
                errorCode = EVP_DigestSignFinal(context, signature, &signatureLen);
                handleEVPError(errorCode, "Failed to finalize evp for JWT");

                return util::filter::encodeBase64(
                        std::string(reinterpret_cast<const char*>(signature), signatureLen));
        }
        void Generator::handleEVPError(int errorCode, const std::string_view& message) {
                if (errorCode != 1) {
                        util::log::error(message);
                }
        }
}

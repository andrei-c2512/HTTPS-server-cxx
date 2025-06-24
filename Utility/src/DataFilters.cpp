#include "Utility/DataFilters.hpp"

namespace util::filter{
	std::string encodeBase64(const std::string& input) {
            EVP_ENCODE_CTX* ctx = EVP_ENCODE_CTX_new();
            if (!ctx) throw std::runtime_error("Failed to create EVP_ENCODE_CTX");

            EVP_EncodeInit(ctx);

            // Allocate output buffer with a bit of slack
            size_t outLen = 4 * ((input.size() + 2) / 3);
            std::vector<unsigned char> outBuf(outLen + 4); // +4 for final padding

            int outLen1 = 0;
            EVP_EncodeUpdate(ctx, outBuf.data(), &outLen1,
                             reinterpret_cast<const unsigned char*>(input.data()),
                             static_cast<int>(input.size()));

            int outLen2 = 0;
            EVP_EncodeFinal(ctx, outBuf.data() + outLen1, &outLen2);

            EVP_ENCODE_CTX_free(ctx);

            return std::string(reinterpret_cast<char*>(outBuf.data()), outLen1 + outLen2);
	}
	std::string encodeBase64(rapidjson::Document doc) {
		using namespace rapidjson;
		StringBuffer docBuffer;
		Writer<StringBuffer> writer(docBuffer);
		doc.Accept(writer);

		return encodeBase64(docBuffer.GetString());
	}
	std::string decodeBase64(const std::string& encoded) {
            EVP_ENCODE_CTX* ctx = EVP_ENCODE_CTX_new();
            if (!ctx) throw std::runtime_error("Failed to create EVP_ENCODE_CTX");

            EVP_DecodeInit(ctx);

            // Output buffer should be big enough
            std::vector<unsigned char> outBuf(encoded.size());

            int outLen1 = 0;
            int rc = EVP_DecodeUpdate(ctx, outBuf.data(), &outLen1,
                                      reinterpret_cast<const unsigned char*>(encoded.data()),
                                      static_cast<int>(encoded.size()));
            if (rc < 0) {
                EVP_ENCODE_CTX_free(ctx);
                throw std::runtime_error("Base64 decode failed");
            }

            int outLen2 = 0;
            rc = EVP_DecodeFinal(ctx, outBuf.data() + outLen1, &outLen2);
            if (rc < 0) {
                EVP_ENCODE_CTX_free(ctx);
                throw std::runtime_error("Base64 final decode failed");
            }

            EVP_ENCODE_CTX_free(ctx);

            return std::string(reinterpret_cast<char*>(outBuf.data()), outLen1 + outLen2);
	}
}


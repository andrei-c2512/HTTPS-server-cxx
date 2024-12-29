#pragma once
#include "document.h"
#include "openssl/bio.h"
#include "writer.h"
#include "stringbuffer.h"
#include <string>
#include "Common.h"

//called the class like this because OpenSSl seems to call transformation filters , with their BIO things
//I hate macros
class DataFilters {
public:

	static std::string encodeBase64(const std::string& data) {
		BIO* bio = BIO_new(BIO_s_mem());
		BIO* b64 = BIO_new(BIO_f_base64());
		bio = BIO_push(b64, bio);

		BIO_write(bio, data.data(), data.length());
		BIO_flush(bio);

		BUF_MEM* buffer;
		BIO_get_mem_ptr(bio, &buffer);

		std::string result(buffer->data, buffer->length);
		BIO_free_all(bio);
		return result;
	}
	static std::string encodeBase64(rapidjson::Document doc) {
		using namespace rapidjson;
		StringBuffer docBuffer;
		Writer<StringBuffer> writer(docBuffer);
		doc.Accept(writer);

		encodeBase64(docBuffer.GetString());
	}
	static std::string decodeBase64(const std::string& encodedData) {
		BIO* bio = BIO_new_mem_buf(encodedData.data(), encodedData.length());
		BIO* b64 = BIO_new(BIO_f_base64());

		bio = BIO_push(b64, bio);

		BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

		std::vector<char> buffer(encodedData.size());
		int decodedLength = BIO_read(bio, buffer.data(), buffer.size());
		BIO_free_all(bio);

		return std::string(buffer.data(), decodedLength);
	}
};
#pragma once
#include "ConsoleLog.hpp"
#include "document.h"
#include "Common.hpp"
#include "StringHelper.hpp"
#include "writer.h"
#include "stringbuffer.h"


namespace HttpCommon {
	enum class Header {
		CONTENT_TYPE,
		HOST,
		CONTENT_LENGTH,
		AUTHORIZATION,
		ACCEPT,

		COUNT
	};


	enum class Verb {
		GET,
		HEAD,
		POST,
		PUT,
		//added _ cause there is a macro called DELETE , bruh
		_DELETE,
		UPDATE,
		CONNECT,
		OPTIONS,
		TRACE
	};

	enum class ContentType {
		JSON,
		CSS,
		HTML,
		JAVA_SCRIPT
	};
	enum class Version {
		HTTP09,
		HTTP10,
		HTTP11
	};

	enum class StatusCode {
		INVALID,
		INFO,
		SUCESS,
		REDIRECT,
		CLIENT_ERROR,
		SERVER_ERROR
	};
	class Parser {
	public:
		static StatusCode getStatusCode(int16_t statusCode) {
			if (statusCode >= 600) {
				return StatusCode::CLIENT_ERROR;
			}
			else
				return StatusCode(statusCode / 100);
		}
	};

	class HeaderCodex {
	public:
		HeaderCodex& operator=(const HeaderCodex&) = delete;
		HeaderCodex(const HeaderCodex&) = delete;
		std::string headerToString(Header type) {
			return headers[int(type)];
		}
		Header stringToHeader(const std::string& arr) {
			return headerMap[arr];
		}
		static HeaderCodex& get() {
			static HeaderCodex h;
			return h;
		}
	private:
		HeaderCodex() {
			headers = { "Content-type" , "Host" , "Content-Length" , "authorization" };

			if (headers.size() != int(Header::COUNT))
				ConsoleLog::warning("Not all headers are implemented");

			for (auto i = 0; i < headers.size(); i++) {
				headerMap.emplace(headers[i], Header(i));
			}
		}
		std::map<std::string, Header> headerMap;
		std::vector<std::string> headers;
	};

	class VerbCodex {
	public:
		VerbCodex& operator=(const VerbCodex&) = delete;
		VerbCodex(const VerbCodex&) = delete;
		std::string verbToString(Verb type) {
			return verbs[int(type)];
		}
		Verb stringToVerb(const std::string& arr) {
			return verbMap[arr];
		}
		static VerbCodex& get() {
			static VerbCodex h;
			return h;
		}
	private:
		VerbCodex() {
			verbs = { "GET" , "HEAD" , "POST" , "PUT" , "DELETE" , "UPDATE" , "CONNECT" , "OPTIONS" , "TRACE" };

			for (auto i = 0; i < verbs.size(); i++) {
				verbMap.emplace(verbs[i], Verb(i));
			}
		}
		std::map<std::string, Verb> verbMap;
		std::vector<std::string> verbs;
	};

	class VersionCodex {
	public:
		VersionCodex& operator=(const VersionCodex&) = delete;
		VersionCodex(const VersionCodex&) = delete;

		std::string versionToString(Version version) {
			return versions[int(version)];
		}
		Version stringToVersion(const std::string& arr) {
			return versionMap[arr];
		}

		static VersionCodex& get() {
			static VersionCodex h;
			return h;
		}
	public:
		Version defaultVersion = Version::HTTP11;
	private:
		VersionCodex() {

			versions = { "HTTP/0.9" , "HTTP/1.0" , "HTTP/1.1" };
			for (auto i = 0; i < versions.size(); i++) {
				versionMap.emplace(versions[i], Version(i));
			}
		}


		std::map<std::string, Version> versionMap;
		std::vector<std::string> versions;
	};


};

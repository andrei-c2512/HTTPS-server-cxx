#pragma once
#include "ConsoleLog.hpp"
#include "document.h"
#include "Common.hpp"
#include "StringHelper.hpp"
#include "writer.h"
#include "stringbuffer.h"
#include "ConstexprMap.hpp"


namespace HttpCommon {
	enum class Header {
		CONTENT_TYPE,
		HOST,
		CONTENT_LENGTH,
		AUTHORIZATION,
		ACCEPT,
		COUNT,
		INVALID
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
		TRACE,
		COUNT,
		INVALID
	};

	enum class ContentType {
		JSON,
		CSS,
		HTML,
		JAVA_SCRIPT,
		COUNT,
		INVALID
	};
	enum class Version {
		HTTP09,
		HTTP10,
		HTTP11,
		COUNT,
		INVALID
	};

	enum class StatusCode {
		INVALID,
		CONTINUE = 100,
		OK = 200,
		MULTIPLE_CHOICES = 300,
		BAD_REQUEST = 400,
		UNAUTHORIZED = 401,
		SERVER_ERROR = 500
	};
	typedef std::string_view str_v;
	constexpr std::string_view headerArr[] = {str_v("Content-type") , str_v("Host") , str_v("Content-Length")  , str_v("Authorization") , str_v("Accept")};
	constexpr std::string_view verbArr[] = { "GET" , "HEAD" , "POST" , "PUT" , "DELETE" , "UPDATE" , "CONNECT" , "OPTIONS" , "TRACE" };
	constexpr std::string_view versionArr[] = { "HTTP/0.9" , "HTTP/1.0" , "HTTP/1.1" };
	constexpr std::string_view contentTypeArr[] = { "application/json" , "text/css" , "text/html" , "text/javascript" };

	template <typename Enum>
	constexpr std::array<std::pair<str_v, Enum>, size_t(Enum::COUNT)> generateMap(const std::string_view* beg) {
		std::array<std::pair<str_v, Enum>, size_t(Enum::COUNT)> arr;
		for (size_t i = 0; i < arr.size(); i++) {
			arr[i] = std::make_pair(beg[i], (Enum)i);
		}
		return arr;
	}

	constexpr inline ConstexprMap<std::string_view, Header     , size_t(Header::COUNT)     > headerMap      = { generateMap<Header>(&headerArr[0])};
	constexpr inline ConstexprMap<std::string_view, Verb       , size_t(Verb::COUNT)       > verbMap        = { generateMap<Verb>(&verbArr[0])};
	constexpr inline ConstexprMap<std::string_view, Version    , size_t(Version::COUNT)    > versionMap     = { generateMap<Version>(&versionArr[0])};
	constexpr inline ConstexprMap<std::string_view, ContentType, size_t(ContentType::COUNT)> contentTypeMap = { generateMap<ContentType>(&contentTypeArr[0])};


	constexpr Header toHeader(const std::string_view str) noexcept {
		auto it = headerMap.at(str);
		if (it != headerMap.end()) {
			return it->second;
		}
		else
			return Header::INVALID;
	}
	constexpr Verb toVerb(const std::string_view str) noexcept {
		auto it = verbMap.at(str);
		if (it != verbMap.end()) {
			return it->second;
		}
		else
			return Verb::INVALID;
	}
	constexpr Version toVersion(const std::string_view str) noexcept {
		auto it = versionMap.at(str);
		if (it != versionMap.end()) {
			return it->second;
		}
		else
			return Version::INVALID;
	}
	constexpr ContentType toContentType(const std::string_view str) noexcept {
		auto it = contentTypeMap.at(str);
		if (it != contentTypeMap.end()) {
			return it->second;
		}
		else
			return ContentType::INVALID;
	}

	inline Version defaultVersion = Version::HTTP10;
};

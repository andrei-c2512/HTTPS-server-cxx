#pragma once
#include <string>
#include <vector>
#include "Common.hpp"
#include "document.h"
#include "stringbuffer.h"
#include "writer.h"
#include <concepts>

template <typename T>
concept StringPair = std::is_same_v<T, std::pair<const char*, const char*>>;

class StringHelper {
public:
	//returns the next line , including the next line character
	static std::string nextLine(const std::string& str, int32_t& begin) {
		auto copy = begin;
		for (; begin < str.size(); begin++)
		{
			if (str[begin] == '\n')
			{
				return str.substr(copy, begin++ - copy);
			}
		}
		return "";
	}
	static std::string nextLine(const std::string& str, int32_t& begin, int32_t end) {
		auto copy = begin;
		for (; begin < end; begin++)
		{
			if (str[begin] == '\n')
			{
				return str.substr(copy, begin++ - copy);
			}
		}
		return "";
	}
	static std::string jsonToString(const rapidjson::Document& doc) {
		using namespace rapidjson;
		StringBuffer docBuffer;
		Writer<StringBuffer> writer(docBuffer);
		doc.Accept(writer);

		return docBuffer.GetString();
	}

	static size_t jsonCharLength(const rapidjson::Document& doc) {
		using namespace rapidjson;
		StringBuffer docBuffer;
		Writer<StringBuffer> writer(docBuffer);
		doc.Accept(writer);

		return docBuffer.GetSize();
	}

	template<StringPair pair>
	static void addPair(rapidjson::Document& doc, pair p) {
		doc.AddMember(
			rapidjson::Value(p.first, doc.GetAllocator()),
			rapidjson::Value(p.second, doc.GetAllocator()),
			doc.GetAllocator()
		);
	}
	template<StringPair... Pairs>
	static rapidjson::Document createBasicDoc(const Pairs&... pairs) {
		rapidjson::Document doc;
		doc.SetObject();
		(addPair(doc, pairs), ...);
		return doc;
	}
};
			
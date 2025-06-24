#pragma once
#include "Common.hpp"

template <typename T>
concept StringPair = std::is_same_v<T, std::pair<const char*, const char*>>;

namespace util::str{
	//returns the next line , including the next line character
	std::string nextLine(const std::string& str, int32_t& begin);
	std::string nextLine(const std::string& str, int32_t& begin, int32_t end);
	std::string jsonToString(const rapidjson::Document& doc);
	size_t jsonCharLength(const rapidjson::Document& doc);

	template<StringPair pair>
	void addPair(rapidjson::Document& doc, pair p) {
		doc.AddMember(
			rapidjson::Value(p.first, doc.GetAllocator()),
			rapidjson::Value(p.second, doc.GetAllocator()),
			doc.GetAllocator()
		);
	}
	template<StringPair... Pairs>
	rapidjson::Document createBasicDoc(const Pairs&... pairs) {
		rapidjson::Document doc;
		doc.SetObject();
		(addPair(doc, pairs), ...);
		return doc;
	}
};
			

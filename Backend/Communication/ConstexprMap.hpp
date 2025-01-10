#pragma once
#include <array>
#include <exception>

/*
	This class should be used for small-ish data sets( maybe < 20) to implement a compile time map. Despite it doing 
	a liniar search with std::find_if , if used , for example , with string_view(to use string literals) , the compiler 
	greatly optimises the search and makes it 10x faster than a regular map.
*/
template<typename Key , typename Value , size_t Size>
struct ConstexprMap {
	std::array<std::pair<Key, Value>, Size> data;
	[[nodiscard]] constexpr auto at(const Key& key) const noexcept {
		return std::find_if(std::begin(data), std::end(data), [key](const auto& pair) {
			return pair.first == key;
			});
	}
	[[nodiscard]] constexpr auto end() const noexcept {
		return std::end(data);
	}

};
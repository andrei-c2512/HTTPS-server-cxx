#pragma once
#include <vector>
#include <functional>

namespace util::alg {
	template<typename T , typename V>
	void binarySearch(
		const std::vector<T>& list , 
		V value , 
		std::function<V(T)> getter, //requires a lambda that returns the value V, from the object T
		std::function<void(V)> onFound,
		std::function<void()> onNotFound = []() {}) 
	{
		int32_t left = 0, right = list.size() - 1, middle = (left + right) / 2;

		while (left <= right) {
			V val = getter(list[middle]);
			if (val == value)
			{
				onFound(middle);
				return;
			}
			else if (val < value)
				left = middle + 1;
			else
				right = middle - 1;
			middle = (left + right) / 2;
		}
		onNotFound();
	}
}

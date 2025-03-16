#pragma once
#include "Common.hpp"


//this class is almsot the same as the one from javidx video , but hey  ,it does the job
template<typename T>
class TsQueue {
public:
	TsQueue() = default;
	TsQueue(const TsQueue<T>&) = delete;
	const T& front() {
		std::scoped_lock lock(mDeq);
		return deq.front();
	}
	const T& back() {
		std::scoped_lock lock(mDeq);
		return deq.back();
	}
	void push_back(const T& item) {
		std::scoped_lock lock(mDeq);
		deq.emplace_back(item);
	}
	void push_front(const T& item) {
		std::scoped_lock lock(mDeq);
		deq.emplace_front(item);
	}
	bool empty() const {
		std::scoped_lock lock(mDeq);
		return deq.empty();
	}
	size_t size() const {
		std::scoped_lock lock(mDeq);
		return deq.size();
	}
	void clear() {
		std::scoped_lock lock(mDeq);
		deq.clear();
	}
	T pop_front() {
		std::scoped_lock lock(mDeq);
		T first = std::move(deq.front());
		deq.pop_front();
		return first;
	}
	T pop_back() {
		std::scoped_lock lock(mDeq);
		T last = std::move(deq.back());
		deq.pop_back();
		return last;
	}
protected:
	mutable std::mutex mDeq;
	std::deque<T> deq;
};

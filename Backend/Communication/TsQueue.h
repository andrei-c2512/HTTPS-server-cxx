#pragma once
#include "Common.h"


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
		return lock.empty();
	}
	size_t size() const {
		std::scoped_lock lock(mDeq);
		return deq.size();
	}
	void clear() {
		std::scoped_lock lock(mDeq);
		return deq.size();
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
	std::mutex mDeq;
	std::deque<T> deq;
};

#pragma once
#include "Common.hpp"

class Message {
public:
	Message() = default;
	virtual std::string toString() const { return ""; }
	int32_t userId() const noexcept {
		return _userId;
	}
	void setUserId(int32_t userId) noexcept {
		_userId = userId;
	}
	void setNull(bool null0) noexcept {
		null = null0;
	}
	bool isNull() const noexcept {
		return null;
	}
protected:
	int32_t _userId; 
	bool null = false;
};


template <typename T>
concept message = std::is_base_of_v<Message, T>;


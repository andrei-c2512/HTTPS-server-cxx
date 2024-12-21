#pragma once
#include "Common.h"


template<IsSocket socketType>
class AbstractMessageReader {
public:
	AbstractMessageReader() = default;
	virtual void start(socketType& socket) = 0;
	virtual std::string messageString() const = 0;
	bool ready() const noexcept { return _ready; }
	int32_t userId() const noexcept {
		return _userId;
	}
	void setUserId(int32_t userId) noexcept {
		_userId = userId;
	}
protected:
	bool _ready = false;
	int32_t _userId = -1;
};


#pragma once
#include "Common.h"


template<IsSocket socketType>
class AbstractMessageReader {
public:
	AbstractMessageReader() = default;
	virtual void start(socketType& socket) = 0;
	virtual std::string messageString() const = 0;
	bool ready() const noexcept { return _ready; }
protected:
	bool _ready = false;
};


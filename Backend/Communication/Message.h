#pragma once
#include "Common.h"

class Message {
public:
	enum class Type {
		Custom,
		Http,
		Https
	};
public:
	Message() = default;
	virtual ByteArray toByteArray() const {}
};
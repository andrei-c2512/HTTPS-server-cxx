#pragma once
#include "Common.h"

class Message {
public:
	Message() = default;
	virtual ByteArray toByteArray() const {}
	virtual std::string toString() const {}
};


template <typename T>
concept message = std::is_base_of_v<Message, T>;


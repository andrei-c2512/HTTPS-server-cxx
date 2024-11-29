#pragma once
#include "Common.h"

class Message {
public:
	Message() = default;
	virtual std::string toString() const { return ""; }
};


template <typename T>
concept message = std::is_base_of_v<Message, T>;


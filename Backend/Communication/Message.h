#pragma once
#include <string>

class Message {
public:
	Message() = default;
	virtual std::string toString() const {}
};
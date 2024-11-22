#pragma once
#include <string>

class Message {
public:
	enum class Type {
		Custom,
		Http,
		Https
	};
public:
	Message() = default;
	virtual std::string toString() const {}
};
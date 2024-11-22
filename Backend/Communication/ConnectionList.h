#pragma once
#include <vector>
#include <list>
#include <memory>
#include "Connection.h"

class ConnectionList {
public:
	ConnectionList() = default;
	bool add(std::shared_ptr<Connection> conn);
	//this one also gives it an id
	bool addNew(std::shared_ptr<Connection> conn);
	void remove(int32_t id);
	std::shared_ptr<Connection> get(int32_t id) const;
private:
	//I won't use std::list despite constant add/remove because searching for a specific id would be costly with it
	// I can use binary search on a vector
	std::vector<std::shared_ptr<Connection>> list;
	int32_t nextId = 0;
};
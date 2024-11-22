#include "ConnectionList.h"
#include <algorithm>
#include "ConsoleLog.h"
#include "Algo.h"

bool ConnectionList::add(std::shared_ptr<Connection> conn) {
	auto it = std::lower_bound(list.begin(), list.end(), conn->id());
	list.insert(it, conn);
}
bool ConnectionList::addNew(std::shared_ptr<Connection> conn) {
	conn->setId(nextId);
	nextId++;
	add(conn);
}
//this is still quite innefficient
void ConnectionList::remove(int32_t id) {
	int32_t left = 0, right = list.size(), middle = (left + right) / 2;

	while (left <= right) {
		int32_t val = list[middle]->id();
		if (val == id)
		{
			//inefficent because of this
			list.erase(list.begin() + middle);
			ConsoleLog::info("Client removed");
			return;
		}
		else if (val < id)
			left = middle + 1;
		else
			right = middle - 1;
	}
	ConsoleLog::warning("Did not find any client with an id of <" + std::to_string(id) + ">");

	/*auto onFound = [this](int32_t middle) {
		list.erase(list.begin() + middle);
		ConsoleLog::info("Client removed");
		};
	auto onNotFound = [this, id]() {
		ConsoleLog::warning("Did not find any client with an id of <" + std::to_string(id) + ">");
		};
	auto getter = [](std::shared_ptr<Connection> conn) {
		return conn->id();
		};


	Algo::binarySearch(list, id , getter , onFound , onNotFound);*/
	
}

std::shared_ptr<Connection> ConnectionList::get(int32_t id) const {
	int32_t left = 0, right = list.size(), middle = (left + right) / 2;

	while (left <= right) {
		int32_t val = list[middle]->id();
		if (val == id)
		{
			return list[middle];
		}
		else if (val < id)
			left = middle + 1;
		else
			right = middle - 1;
	}
	ConsoleLog::warning("Did not find any client with an id of <" + std::to_string(id) + ">");
	return nullptr;
}


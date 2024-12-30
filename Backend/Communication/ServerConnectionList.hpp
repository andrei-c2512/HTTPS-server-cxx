#pragma once
#include "ConsoleLog.hpp"


template <typename T , typename msgOut>
class ServerConnectionList {
public:
	ServerConnectionList() = default;
	bool add(std::shared_ptr<T> conn) {
		auto it = std::lower_bound(list.begin(), list.end(), conn->id(),
			[](std::shared_ptr<T> l, int32_t val) {
				return l->id() < val;
			});
		list.insert(it, conn);
		return true;
	}
	//this one also gives it an id
	bool addNew(std::shared_ptr<T> conn) {
		conn->setId(nextId);
		nextId++;
		add(conn);
		return true;
	}
	//this is still quite innefficient
	void remove(int32_t id) {
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

	std::shared_ptr<T> get(int32_t id) const {
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
	void sendMessage(std::shared_ptr<msgOut> message , int32_t id) {
		auto user = get(id);
		user->send(message);
	}
private:
	//I won't use std::list despite constant add/remove because searching for a specific id would be costly with it
	// I can use binary search on a vector
	std::vector<std::shared_ptr<T>> list;
	int32_t nextId = 0;
};


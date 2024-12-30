#pragma once
#include "Common.hpp"
#include "TsQueue.hpp"

template <typename Key , typename messageIn , typename messageOut>
class AbstractResponseHandler {
public:
	AbstractResponseHandler() = default;
	virtual void initHandlerMap() = 0;
	std::shared_ptr<messageOut> handleMessage(std::shared_ptr<messageIn> msg) {
		assert(handlerSet);
		return currentHandler(msg);
	}
	void setNextHandler(Key key) {
		auto handlerMapIt = handlerMap.find(key);
		if (handlerMapIt != handlerMap.end()) {
			currentHandler = *handlerMapIt;
			handlerSet = true;
		}
		else {
			ConsoleLog::error("Invalid handler key: did not process response");
		}
	}
protected:
	std::map<Key , 
		std::function<std::shared_ptr<messageOut>(std::shared_ptr<messageIn>)>> handlerMap;

	std::function<std::shared_ptr<messageOut>(std::shared_ptr<messageIn>)> currentHandler;
	bool handlerSet = false;
};
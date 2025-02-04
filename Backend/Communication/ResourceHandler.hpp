#pragma once
#include "Common.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "BaseHandlingContext.hpp"

/*
* pointer to handling context to avoid slicing cuz maybe I want to extend it at some point
* Maybe some contexts will have a JWT validator , maybe some oAuth crap , idk. Web page delivery is the base of it only
*/
typedef ResponsePtr(*HttpHandler)(RequestPtr , BaseHandlingContext*);

class ResourceHandler {
public:
	ResourceHandler(BaseHandlingContext* ctx0) noexcept
		:ctx(ctx0)
	{
		//this is more or less a safety measure in case I am dumb and modify the enum type wrongly
		_handleList.fill(defaultHandler());

		using namespace HttpCommon;
		_handleList[(size_t)Verb::GET] = GET_handler();
		_handleList[(size_t)Verb::POST] = POST_handler();
		_handleList[(size_t)Verb::UPDATE] = UPDATE_handler();
		_handleList[(size_t)Verb::_DELETE] = DELETE_handler();
	}
	[[nodiscard]] ResponsePtr handle(RequestPtr req) const  {
		assert(((size_t)req->verb() >= 0 && (size_t)req->verb() < (size_t)HttpCommon::Verb::COUNT) &&
				"Out of bounds verb called");

		return _handleList[(size_t)req->verb()](req, ctx);
	}
protected:
	static HttpHandler defaultHandler() noexcept {
		auto handler = []([[maybe_unused]] RequestPtr req , [[maybe_unused]] BaseHandlingContext* ctx ) -> ResponsePtr {
			return HttpResponse::createErrorResponse("Unavailable method for this resource");
		};

		return static_cast<HttpHandler>(handler);
	}
	/*
	*  Pls do not implement this with captured lambdas because I am using raw pointers => 
	*	unsafe ( it allocates the captured stuff on the heap)
	* 
	*	Nevermind you will get an error anyway lol(tested it)
	*/
	virtual HttpHandler GET_handler() const noexcept {	return defaultHandler();}
	virtual HttpHandler POST_handler() const noexcept { return defaultHandler();}
	virtual HttpHandler DELETE_handler() const noexcept { return defaultHandler(); }
	virtual HttpHandler UPDATE_handler() const noexcept { return defaultHandler(); }

	void update() noexcept {
		using namespace HttpCommon;
		_handleList[(size_t)Verb::GET] = GET_handler();
		_handleList[(size_t)Verb::POST] = POST_handler();
		_handleList[(size_t)Verb::UPDATE] = UPDATE_handler();
		_handleList[(size_t)Verb::_DELETE] = DELETE_handler();
	}
private:
	std::array<HttpHandler, size_t(HttpCommon::Verb::COUNT)> _handleList;
	BaseHandlingContext* ctx;
};
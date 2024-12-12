#pragma once
#include "HttpServerConnection.h"
#include "BasicServer.h"

/*
	How the server works:
		-when it starts , it listens for connections and adds them to the connection list
		-if you call listen() it starts listening for messages
		-every connection has a reference to the incoming messages queue from the server. Every connection handles incoming data
		from their own socket and adds it to the message queue. 
*/


class HttpServer : public BasicServer<HttpServerConnection, HttpRequest> {
public:
	HttpServer(int16_t port)
		:BasicServer<HttpServerConnection, HttpRequest>(port)
	{}
}; 

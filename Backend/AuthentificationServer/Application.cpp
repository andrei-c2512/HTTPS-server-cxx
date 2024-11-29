#include <iostream>
#include "Server.h"
#include <conio.h>

int main()
{
	Server server(3756);
	server.start();

	while (!_kbhit()) {
		server.update();
	}
	//AbstractServer<HttpServerConnection, HttpRequest> s(3756);
	//s.start();

	return 0;
}
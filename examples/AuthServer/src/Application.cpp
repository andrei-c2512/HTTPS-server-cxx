#include <iostream>
#include "AuthServer/Server.hpp"
#include <unistd.h>

int main()
{
	Server server(3756);
        server.update();
        /*
	try {
		server.start();

		while (true) {
			server.update();

			if (_kbhit()) {
				char ch(_getch());
				switch (ch) {
				case 'q':
					return 0;
				case 's':
					//ConsoleLog::info(std::to_string(server.dbHandler.conn->is_open()));
					break;
				}
			}
		}
		//AbstractServer<HttpServerConnection, HttpRequest> s(3756);
		//s.start();
	}
	catch (const std::exception& e) {
                util::log::error(e.what());
		server.stop();
	}
        */
	server.stop();
	return 0;
}

#include <iostream>
#include "Client.h"
#include <conio.h>
#include <thread>
#include "JWTgenerator.h"

int main()
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    Client client;
    client.registerTest();

    ConsoleLog::info("Decoded shit: " + DataFilters::decodeBase64("SGVsbG8sIE9wZW5TU0wgaW4gQysrIQ=="));
    _getch();
    return 0;
}


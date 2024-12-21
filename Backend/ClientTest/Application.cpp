#include <iostream>
#include "Client.h"
#include <conio.h>
#include <thread>
#include "JWTgenerator.h"

int main()
{
    Client client;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    client.sendTestMessage("JsonTest1.txt");

    ConsoleLog::info("Decoded shit: " + DataFilters::decodeBase64("SGVsbG8sIE9wZW5TU0wgaW4gQysrIQ=="));
    _getch();
    return 0;
}


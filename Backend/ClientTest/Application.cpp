#include <iostream>
#include "Client.h"
#include <conio.h>
#include <thread>

int main()
{
    Client client;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //client.sendTestMessage("JsonTest1.txt");

    _getch();
    return 0;
}


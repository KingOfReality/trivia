#include "Server.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

//class Server;
int main()
{  // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return 1;
    }
    RequestHandlerFactory r;
    SqliteDataBase* db = new SqliteDataBase();
    Server s(r,db);
    s.run();
    WSACleanup();

    return 0;
}
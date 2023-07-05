#include "Server.h"
#include <exception>
#include <iostream>
std::string GetErrorMessage(DWORD errorCode)
{
    LPSTR buffer = nullptr;
    DWORD result = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPSTR>(&buffer),
        0,
        NULL);

    if (result != 0 && buffer != nullptr)
    {
        std::string errorMessage(buffer);
        LocalFree(buffer);
        return errorMessage;
    }

    return "Failed to get error message.";
}
Server::Server(RequestHandlerFactory& r, SqliteDataBase* sql) try: m_handleFactory(r), m_communicator(m_handleFactory),m_database(sql)
{
    WSAInitializer wsa_init;
   
}
catch (std::exception& e)
{
    DWORD errorCode = WSAGetLastError();

    std::string errorMessage = GetErrorMessage(errorCode);
    std::cout << "Error: " << errorMessage << std::endl;
}

bool Server::run()
{
    

        this->m_communicator.serve(9999);
        return true;
   
}

#pragma once
#include "WSAInitializer.h"
#include <map>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;
class IRequestHandler;
class Communicator
{
public:
	Communicator(RequestHandlerFactory& r);
	~Communicator();
	void serve(int port);
private:
	RequestHandlerFactory& m_handlerFactory;
	void acceptClient();
	void clientHandler(SOCKET clientSocket);
	SOCKET _serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
};
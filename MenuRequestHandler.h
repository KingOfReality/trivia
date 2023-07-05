#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;
struct RequestResult;
struct RequestInfo;
class RoomManager;
class LoginRequestHandler;
class MenuRequestHandler:public IRequestHandler
{
private:
	LoggedUser m_user;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult signOut(RequestInfo r);
	RequestResult getRooms(RequestInfo r);
	RequestResult getPlayersInRoom(RequestInfo r);

	//stats/highScore

	RequestResult joinRoom(RequestInfo r);
	RequestResult createRoom(RequestInfo r);




public:
	MenuRequestHandler(LoggedUser& l, RequestHandlerFactory& rhf);
	bool isRequestRelevant(RequestInfo r);
	RequestResult handleRequest(RequestInfo r);
};
				
#ifndef _ROOM_ADMIN
#define _ROOM_ADMIN
 // !_ROOM_ADMIN

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"
//#pragma once

class RequestHandlerFactory;
struct RequestResult;
struct RequestInfo;
class RoomManager;
class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler :public IRequestHandler
{
private:
	RequestHandlerFactory& m_handlerFactory;
	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;


	RequestResult startGame(RequestInfo r);
	RequestResult closeRoom(RequestInfo r);
	RequestResult getRoomState(RequestInfo r);


public:
	RoomAdminRequestHandler(LoggedUser l, RequestHandlerFactory& rhf, Room m_room);
	bool isRequestRelevant(RequestInfo r);
	RequestResult handleRequest(RequestInfo r);
};

#endif

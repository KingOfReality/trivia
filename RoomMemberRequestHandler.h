#ifndef _ROOM_MEMBER
#define _ROOM_MEMBER
 // !ROOM_MEMBER

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
//#pragma once

//#include "MenuRequestHandler.h"
class RequestHandlerFactory;
struct RequestResult;
struct RequestInfo;
class RoomManager;
class LoginRequestHandler;
//class MenuRequestHandler;
class RoomMemberRequestHandler :public IRequestHandler
{
private:
	RequestHandlerFactory& m_handlerFactory;
	Room& m_room;
	LoggedUser& m_user;
	RoomManager& m_roomManager;


	RequestResult leaveRoom(RequestInfo r);
	RequestResult getRoomState(RequestInfo r);


public:
	RoomMemberRequestHandler(LoggedUser& l, RequestHandlerFactory& rhf, Room& m_room);
	bool isRequestRelevant(RequestInfo r);
	RequestResult handleRequest(RequestInfo r);
};

#endif
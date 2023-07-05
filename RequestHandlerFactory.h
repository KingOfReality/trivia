#ifndef REQUESTHANDLERFACTORY_H
#define REQUESTHANDLERFACTORY_H
#pragma once
#include "LoginManager.h"
#include "SqliteDataBase.h"
#include "LoginRequestHandler.h"
#include "RoomManager.h"
#include "GameManager.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameRequestHandler.h"
class LoginRequestHandler;
class MenuRequestHandler;
class Communicator;
class LoginManager;
class GameRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class RequestHandlerFactory
{
private:
	LoginManager m_loginManager;
	IDatabase* m_database;
	RoomManager m_roomManager;
	GameManager m_gameManager;
public:
	GameRequestHandler* createGameRequestHandler(LoggedUser& l, GameData& g);
	GameManager& getGameManager();
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser l);
	RoomManager& getRoomManager();
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser& l,Room& r);
	RoomMemberRequestHandler* creatRoomMemberRequestHandler(LoggedUser& l, Room& r);
};


#endif // REQUESTHANDLERFACTORY_H

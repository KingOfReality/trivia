#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;
struct RequestResult;
struct RequestInfo;
class RoomManager;
class LoginRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler :public IRequestHandler
{
private:
	LoggedUser m_user;
	RequestHandlerFactory& m_handlerFactory;
	GameManager& m_gameManager;
	GameData& m_game;
	RequestResult getQuestion(RequestInfo r);
	RequestResult submitAnswer(RequestInfo r);
	RequestResult getGameResult(RequestInfo r);
	RequestResult leaveGame(RequestInfo r);


public:
	GameRequestHandler(LoggedUser& l, RequestHandlerFactory& rhf, GameData& g);
	bool isRequestRelevant(RequestInfo r);
	RequestResult handleRequest(RequestInfo r);
};

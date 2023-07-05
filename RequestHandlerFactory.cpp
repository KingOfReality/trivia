#include "RequestHandlerFactory.h"
#include <iostream>

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(LoggedUser& l,GameData& gd)
{

    GameRequestHandler* g = new GameRequestHandler(l, *this, gd);
    return g;
}

GameManager& RequestHandlerFactory::getGameManager()
{
    return m_gameManager;
}


LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
   return new LoginRequestHandler(*this);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return m_loginManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser l)
{
    MenuRequestHandler* m = new MenuRequestHandler(l,*this);
    return m;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
    return m_roomManager;

}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser& l, Room& r)
{
    std::cout << "RequestHandlerFactory: " << r.getRoom().name << std::endl;

    return new RoomAdminRequestHandler(l,*this,r);
}

RoomMemberRequestHandler* RequestHandlerFactory::creatRoomMemberRequestHandler(LoggedUser& l, Room& r)
{
    return new RoomMemberRequestHandler(l, *this, r);
}

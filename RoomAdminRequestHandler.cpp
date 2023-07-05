    #include "RoomAdminRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include <iostream>
RequestResult RoomAdminRequestHandler::startGame(RequestInfo r)
{
    this->m_roomManager.getRoom(this->m_room.getRoom().id).getRoom().active = true ;
    StartGameRespone s;
    s.status = 1;
    std::cout << "timeeeeeeee";
    RequestResult req;
    req.Buffer = JsonResponsePacketSerializer::serializerRespone(s);
    req.newHandler = this->m_handlerFactory.createGameRequestHandler(this->m_user, this->m_handlerFactory.getGameManager().createGame(this->m_roomManager.getRoom(this->m_room.getRoom().id), this->m_handlerFactory.getRoomManager().getRoom(this->m_room.getRoom().id).getUsers(),this->m_user));

    return req;
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo r)
{
    
    this->m_roomManager.deleteRoom(this->m_room.getRoom().id);
    std::cout << 11111;
    CloseRoomRespone c;
    c.status = 1;
    RequestResult req;
    req.Buffer = JsonResponsePacketSerializer::serializerRespone(c);
    req.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);

    return req;
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo r)
{
    GetRoomStateRespone g;
    
    g.players = this->m_roomManager.getRoom(this->m_room.getRoom().id).getAllUsers();


    g.answerTimeOut = this->m_room.getRoom().avgTime;

    g.questionCount = this->m_room.getRoom().numOfQuestion;

    g.status = 1;
    g.gameBegun = this->m_room.getRoom().active;

    RequestResult req;
    req.Buffer = JsonResponsePacketSerializer::serializerRespone(g);
    req.newHandler = this;

    return req;
}

RoomAdminRequestHandler::RoomAdminRequestHandler(LoggedUser l, RequestHandlerFactory& rhf, Room m_room):m_handlerFactory(rhf),m_user(l),m_room(m_room),m_roomManager(rhf.getRoomManager())
{
    std::cout << "Constructor: " << this->m_room.getRoom().name << std::endl;

}


bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo r)
{
    if (r.id >= 20 && r.id < 23)
        return true;
    return false;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo r)
{
  
    switch (r.id)
    {
    case 20:
    {
        return closeRoom(r);
        break;
    }case 21:
    {
        return getRoomState(r);
        break;

    }
    case 22:
    {
        return startGame(r);
        break;


    }
    
    }
}

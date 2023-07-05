#include "RoomMemberRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include <iostream>
RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo r)
{
    this->m_roomManager.getRoom(this->m_room.getRoom().id).removeUser(this->m_user);
    LeaveRoomRespone l;
    l.status = 1;
    RequestResult req;
    req.Buffer = JsonResponsePacketSerializer::serializerRespone(l);
    req.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
    return req;
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo r)
{
    ErrorRespone e;
    GetRoomStateRespone g;
    if (this->m_roomManager.getRoom(this->m_room.getRoom().id).getRoom().id == -1)
    {
        e.message = "Room doesnt exist!";
        RequestResult req;
        req.Buffer = JsonResponsePacketSerializer::serializerRespone(g);
        req.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
        return req;
    }
    g.players = this->m_roomManager.getRoom(this->m_room.getRoom().id).getAllUsers();
    g.answerTimeOut = this->m_room.getRoom().avgTime;
    g.questionCount = this->m_room.getRoom().numOfQuestion;
    g.status = 1;
    g.gameBegun = this->m_roomManager.getRoom(this->m_room.getRoom().id).getRoom().active;
    RequestResult req;
    req.Buffer = JsonResponsePacketSerializer::serializerRespone(g);

    if (g.gameBegun)
    {
        std::cout << "you got in!";
       
        req.newHandler = this->m_handlerFactory.createGameRequestHandler(this->m_user, this->m_handlerFactory.getGameManager().getGame(this->m_room.getRoom().id,this->m_user));
        std::cout << "you got out!";

    }
    else
        req.newHandler = this;

    return req;
}

RoomMemberRequestHandler::RoomMemberRequestHandler(LoggedUser& l, RequestHandlerFactory& rhf, Room& m_room):m_handlerFactory(rhf),m_roomManager(rhf.getRoomManager()),m_room(m_room),m_user(l)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo r)
{
    if (r.id >= 30 && r.id < 32)
        return true;
    return false;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo r)
{
    switch (r.id)
    {
    case 30:
        return getRoomState(r);
        break;
    case 31:
           return  leaveRoom(r);
           break; 
    }
    return getRoomState(r);
}

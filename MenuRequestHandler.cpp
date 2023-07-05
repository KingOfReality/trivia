
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "json.hpp"
#include <string>
#include <iostream>
#include <bitset>
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
class MenuRequestHandler;
class JsonResponsePacketSerializer;
class RequestHandlerFactory;
RequestResult MenuRequestHandler::signOut(RequestInfo r)
{
    LogOutRespone l;
    RequestResult requestResult;
    l.status = 1;
    requestResult.Buffer = JsonResponsePacketSerializer::serializerRespone(l);
    requestResult.newHandler = this->m_handlerFactory.createLoginRequestHandler();
    return requestResult;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo r)
{
    GetRoomRespone g;
    RequestResult requestResult;
    g.rooms = this->m_handlerFactory.getRoomManager().getRooms();
    requestResult.Buffer = JsonResponsePacketSerializer::serializerRespone(g);
    requestResult.newHandler  = this;
    return requestResult;
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo r)
{
    GetPlayersInRoomRequest g  =   JsonRequestPacketDeserializer::deserializeGetPlayersRequest(r.v);
    GetPlayerInRoomRespone res;
    RequestResult requestResult;
    std::vector<std::string> temp;
    for (int i = 0; i < this->m_handlerFactory.getRoomManager().getRoom(g.roomId).getAllUsers().size(); i++)
    {
        temp.push_back(this->m_handlerFactory.getRoomManager().getRoom(g.roomId).getAllUsers()[i]);
    }
    res.players = temp;
    requestResult.Buffer = JsonResponsePacketSerializer::serializerRespone(res);
    requestResult.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
    return requestResult;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo r)
{
    JoinRoomRequest j = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(r.v);
    JoinRoomRespone res;
    RequestResult requestResult;
    try
    {
        this->m_handlerFactory.getRoomManager().getRoom(j.roomId).addUser(this->m_user);

    }
    catch (std::string& e)
    {

    }
    res.status = 1;
    requestResult.Buffer = JsonResponsePacketSerializer::serializerRespone(res);
    requestResult.newHandler = this->m_handlerFactory.creatRoomMemberRequestHandler(this->m_user, this->m_handlerFactory.getRoomManager().getRoom(j.roomId));
    return requestResult;
}
bool checkIfExist(std::vector<RoomData> r,int id)
{

    for (int i = 0; i < r.size(); i++)
    {
        if (r[i].id == id)
            return false;
    }
    return true;
}
RequestResult MenuRequestHandler::createRoom(RequestInfo r)
{
    CreateRoomRequest c = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(r.v);
    ErrorRespone err;
    CreateRoomRespone res;
    RoomData data;
    int roomId = 1;
    while (!checkIfExist(this->m_handlerFactory.getRoomManager().getRooms(), roomId))
    {
        roomId++;
    }
    data.id = roomId;
    data.maxPlayers = c.maxUsers;
    data.avgTime = c.answerTimeOut;
    data.name = c.roomName;
    data.numOfQuestion = c.questionCount;
    data.active = false;
    RequestResult requestResult;
    try
    {
        this->m_handlerFactory.getRoomManager().createRoom(this->m_user, data);
    }
    catch (std::string& e)
    {
        err.message = e;
        requestResult.Buffer = JsonResponsePacketSerializer::serializerRespone(err);
        requestResult.newHandler = this;
        return requestResult;
    }
    res.status = 1;
    res.id = data.id;
    Room room(data);
    this->m_handlerFactory.getRoomManager().getRoom(data.id).addUser(this->m_user);
    requestResult.Buffer = JsonResponsePacketSerializer::serializerRespone(res);
    requestResult.newHandler = this->m_handlerFactory.createRoomAdminRequestHandler(this->m_user, room);
    return requestResult;
}

MenuRequestHandler::MenuRequestHandler(LoggedUser& l, RequestHandlerFactory& rhf) :m_handlerFactory(rhf), m_user(l)
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo r)
{
    if (r.id >= 10 && r.id < 15)
        return true;
    return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo r)
{
    if (!isRequestRelevant(r))
    {
        std::cout << "1132321312:     " << r.id;
        throw("error!");
    }
    switch (r.id)
    {
    case 10:
        return signOut(r);
        break;
    case 11:
        return getRooms(r);
        break;
    case 12:
        return getPlayersInRoom(r);
        break;
    case 13:
        return joinRoom(r);
        break;
    case 14:
        return createRoom(r);
        break;
 
    }
    
}

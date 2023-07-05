#include "RoomManager.h"
#include <iostream>
class Room;
bool RoomManager::createRoom(LoggedUser l, RoomData r)
{
    Room room(r);
    this->m_room[r.id] = room;
    return true;
}

bool RoomManager::deleteRoom(int id)
{
    this->m_room.erase(id);
    std::cout << "ewfgergfe";
    return true;
}

unsigned int RoomManager::getRoomState(int ID)
{
    return  this->m_room[ID].getRoom().active;
}

std::vector<RoomData> RoomManager::getRooms()
{
    std::vector<RoomData> temp;
    std::map<int, Room>::iterator it;
    for (it = this->m_room.begin(); it != this->m_room.end(); it++)
    {
        if (it->second.getRoom().maxPlayers > it->second.getUsers().size())
            temp.push_back(it->second.getRoom());
    }
    return temp;
}

Room& RoomManager::getRoom(int ID)
{

    return this->m_room[ID];

}

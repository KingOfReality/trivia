#pragma once
#include "Room.h"
#include <map>

class RoomManager
{
private:
	std::map<int, Room> m_room;
public:
	bool createRoom(LoggedUser l, RoomData r);
	bool deleteRoom(int id);
	unsigned int getRoomState(int ID);
	std::vector<RoomData> getRooms ();
	Room& getRoom(int ID);

};
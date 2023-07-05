#pragma once
#include <string>
#include "LoggedUser.h"
#include <vector>
struct RoomData
{
    unsigned int id;
    std::string name;
    unsigned int maxPlayers;
    unsigned int avgTime;
    unsigned int active;
    unsigned int numOfQuestion;


}typedef;

class Room
{
    RoomData m_metaData;
    std::vector<LoggedUser> m_users;
public:
    Room();
    Room(RoomData data);
    bool addUser(LoggedUser l);
    bool removeUser(LoggedUser l);
    std::vector<std::string> getAllUsers();
    std::vector<LoggedUser> getUsers();

    RoomData& getRoom();
    
};

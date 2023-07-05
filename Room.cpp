#include "Room.h"
#include <iostream>

Room::Room()
{
    this->m_metaData.id = -1;
}

Room::Room(RoomData data):m_metaData(data)
{
    this->m_users.clear();
}

bool Room::addUser(LoggedUser l)
{
	try
	{
		this->m_users.push_back(l);
	}
	catch (std::string e)
	{
        throw("invalid");
        return false;
	}
	return true;
}

bool Room::removeUser(LoggedUser l)
{
    try
    {
        // Find the user in the vector of users
        auto it = std::find(m_users.begin(), m_users.end(), l);

        // If the user is found, remove it from the vector
        if (it != m_users.end())
        {
            m_users.erase(it);
            return true;
        }
        else
        {
            // User not found
            throw std::string("User not found in the room.");
        }
    }
    catch (std::string e)
    {
        std::cout << e;
        return false;
    }
}


std::vector<std::string> Room::getAllUsers()
{
    std::vector<std::string> temp;
    if (this->m_users.empty())
        return temp;
    for (int i = 0; i < this->m_users.size(); i++)
    {

        temp.push_back(this->m_users[i].getUsername());

    }
    return temp;
}

std::vector<LoggedUser> Room::getUsers()
{
    return this->m_users;
}

RoomData& Room::getRoom()
{
    return this->m_metaData;
}

#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string m_username)
{
    this->m_username = m_username;
}

std::string LoggedUser::getUsername()
{
    return this->m_username;
}

bool LoggedUser::operator==(const LoggedUser& other) const
{
    // Implement the comparison logic based on your requirements
    return (this->m_username == other.m_username );
}



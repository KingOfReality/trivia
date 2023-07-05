#pragma once
#include <string>
class LoggedUser
{
private:
	std::string m_username;
public:
	LoggedUser(std::string m_username);
	std::string getUsername();
	bool operator==(const LoggedUser& other) const;
};
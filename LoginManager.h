#pragma once
#include "SqliteDataBase.h"
#include <vector>
#include "LoggedUser.h"
class LoginManager
{
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
public:
	int signup(std::string username, std::string password, std::string email);
	int login(std::string username, std::string password);
	void logout(std::string username);


};
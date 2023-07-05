#include "LoginManager.h"

int LoginManager::signup(std::string username, std::string password, std::string email)
{
	SqliteDataBase s;
	s.open();
	if (s.addNewUser(username, password,email))
		return true;
	return false;
}

int LoginManager::login(std::string username, std::string password)
{
	SqliteDataBase s;

	s.open();
	for (int i = 0; i < this->m_loggedUsers.size(); i++)
	{
		if (this->m_loggedUsers[i].getUsername() == username)
			return false;
	}
	LoggedUser l(username);

	if (s.doesPasswordMatch(username, password))
	{
		this->m_loggedUsers.push_back(l);
		return true;
	}
	return false;

}

void LoginManager::logout(std::string username)
{
	auto it = std::find_if(m_loggedUsers.begin(), m_loggedUsers.end(),
		[username]( LoggedUser& user) {
			return user.getUsername() == username;
		});

	if (it != m_loggedUsers.end())
	{
		m_loggedUsers.erase(it);
	}
}


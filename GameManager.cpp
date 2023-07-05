#include "GameManager.h"
#include "SqliteDataBase.h"
#include <iostream>


GameData& GameManager::createGame(Room r,  std::vector< LoggedUser> m_user,LoggedUser user)
{
    SqliteDataBase s;
    s.open();
    Game game;
    std::list<Question> l = s.getQuestions(r.getRoom().numOfQuestion);
    std::vector<Question> v(l.begin(), l.end());
    for (int i = 0; i < v.size(); i++)
    {
        std::cout << "the Quest: " << v[i].getQuestion() << std::endl;
    }
  
    std::cout << "Maybe its here";

    for (int i = 0; i < m_user.size();i++)
    {
        GameData* g = new GameData(v, m_user[i], r.getRoom().id);
        game.games[m_user[i].getUsername()] = *g;
        game.id = r.getRoom().id;
    }
        this->m_games.push_back(game);
        std::cout << "or its there";

    return   this->getGame(r.getRoom().id,user) ;
}

void GameManager::deleteGame(unsigned int id)
{
    for (int i = 0; i < this->m_games.size(); i++)
    {
        if (this->m_games[i].id == id)
            this->m_games.erase(this->m_games.begin() + i);
    }
}

GameData& GameManager::getGame(int id,LoggedUser l)
{
    // TODO: insert return statement here
    for (auto& games : this->m_games)
    {
        std::cout << "   Maybe its not even here  "<<games.id;

        if (games.id == id)
        {

            return games.games[l.getUsername()];
            
        }
    }
}

Game& GameManager::getSpec(int id)
{
    for (auto& games : this->m_games)
    {
        std::cout << "   Maybe its not even here  " << games.id;

        if (games.id == id)
        {

            return games;

        }
    }
    // TODO: insert return statement here
}

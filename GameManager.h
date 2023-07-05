#include "GameData_.h"
#include <vector>
#include "Room.h"
#include "IDatabase.h"
#include <map>
class Room;
class GameData;
struct  Game
{
	std::map<std::string, GameData> games;
	int id;
};
class GameManager
{
	IDatabase* m_database;
	std::vector<Game> m_games;
public:
	GameData& createGame(Room r, std::vector< LoggedUser> m_user,LoggedUser user);
	void deleteGame(unsigned int id);
	GameData& getGame(int id, LoggedUser l);
	Game& getSpec(int id);
};



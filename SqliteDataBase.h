#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
class SqliteDataBase :public IDatabase
{
private:
    sqlite3* db;
public:
    bool open() override;
    int createStatisticsTable();
    bool close() override;
    int doesUserExist(std::string str) override;
    int doesPasswordMatch(std::string pass, std::string passCon) override;
    int addNewUser(std::string userName, std::string password, std::string email) override;
    std::list<Question> getQuestions(int size) override;
    float getPlayerAvgAnswerTime(std::string name) override;
    int getNumOfCorrectAnswers(std::string name) override;
    int getNumOfTotalAnswers(std::string name) override;
    int getNumOFPlayerGames(std::string name) override;
};
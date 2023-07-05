#pragma once
#include <string>
#include "Question.h"
#include <list>
class IDatabase
{
public:
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual int doesUserExist(std::string str) = 0;
	virtual int doesPasswordMatch(std::string pass,std::string passCon) = 0;
	virtual int addNewUser(std::string userName, std::string password, std::string enail) = 0;
	virtual std::list<Question> getQuestions(int size) = 0;
	virtual float getPlayerAvgAnswerTime(std::string name) = 0;
	virtual int getNumOfCorrectAnswers(std::string name) = 0;
	virtual int getNumOfTotalAnswers(std::string name) = 0;
	virtual int getNumOFPlayerGames(std::string name) = 0;


};
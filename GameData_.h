#pragma once
#include <vector>
#include "Question.h"
#include "LoggedUser.h"

class GameData
{
private:
	Question currentQuestion;
	int currentIndex;
	unsigned int correctAnswerCount;
	LoggedUser m_user;
	unsigned int id;
	unsigned int wrongAnswerCount;
	unsigned int avgAnswerTime;
	std::vector<Question> m_questions;
	bool isDone;

public:
	GameData(std::vector<Question> questions, LoggedUser l, unsigned int id);
	GameData();

	// Getters
	Question getCurrentQuestion() const;
	int getCurrentIndex() const;
	unsigned int getCorrectAnswerCount() const;
	LoggedUser getUser() const;
	unsigned int getWrongAnswerCount() const;
	unsigned int getAverageAnswerTime() const;
	std::vector<Question> getQuestions() const;
	unsigned int getId() const;
	bool getIsDone() const;
	// Setters
	void setCurrentQuestion(Question question);
	void addCurrentIndex();
	void addCorrectAnswerCount();
	void addWrongAnswerCount();
	void setAverageAnswerTime(unsigned int time);
	//
	bool submit(int index);

};


#pragma once
#include <string>
#include <vector>
class Question
{
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
	int correctIndex;
public: 
	Question(std::vector<std::string> possibleAnswers, int correctIndex, std::string question);
	std::string getQuestion();
	std::vector<std::string> getPossibleAnswers();
	int getCorrectAnswer();
};
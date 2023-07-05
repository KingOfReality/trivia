#include "GameData_.h"
#include <iostream>

GameData::GameData(std::vector<Question> questions, LoggedUser l ,unsigned int id) : currentQuestion(questions[0]), m_user(l)
{

    this->avgAnswerTime = 0;
    this->correctAnswerCount = 0;
    this->currentIndex = 0;
    this->id = id;
    this->m_questions = questions;
    this->isDone = false;
}

GameData::GameData() :currentQuestion(Question(std::vector<std::string>(), 0, "")), m_user(LoggedUser("adad"))
{
}



Question GameData::getCurrentQuestion() const
{

    return currentQuestion;
}

int GameData::getCurrentIndex() const
{
    return currentIndex;
}

unsigned int GameData::getCorrectAnswerCount() const
{
    return correctAnswerCount;
}

LoggedUser GameData::getUser() const
{
    return m_user;
}

unsigned int GameData::getWrongAnswerCount() const
{
    return wrongAnswerCount;
}

unsigned int GameData::getAverageAnswerTime() const
{
    return avgAnswerTime;
}

std::vector<Question> GameData::getQuestions() const
{
    return m_questions;
}

unsigned int GameData::getId() const
{
    return this->id;
}

bool GameData::getIsDone() const
{
    return this->isDone;
}

void GameData::setCurrentQuestion(Question question)
{
    currentQuestion = question;
}

void GameData::addCurrentIndex()
{
    currentIndex++;
}

void GameData::addCorrectAnswerCount()
{
    correctAnswerCount++;
}



void GameData::addWrongAnswerCount()
{
    wrongAnswerCount++;
}

void GameData::setAverageAnswerTime(unsigned int time)
{
    avgAnswerTime = time;
}

bool GameData::submit(int index)
{
    bool flag;
    if (this->currentQuestion.getCorrectAnswer() == index)
    {
        addCorrectAnswerCount();
        flag = true;
    }
    else
    {
        flag = false;

        addWrongAnswerCount();
    }
    this->currentIndex++;
    
    if (this->currentIndex <= this->m_questions.size() - 1)
        setCurrentQuestion(this->m_questions[currentIndex]);
    else
        this->isDone = true;
    std::cout << "current questions sizeeeeee: "<< this->m_questions.size();
    return flag;
}

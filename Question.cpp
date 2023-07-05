#include "Question.h"

Question::Question(std::vector<std::string> possibleAnswers, int correctIndex, std::string question)
{
    this->correctIndex = correctIndex;
    this->m_possibleAnswers = possibleAnswers;
    this->m_question = question;
}

std::string Question::getQuestion()
{
    return this->m_question;
}

std::vector<std::string> Question::getPossibleAnswers()
{
    return this->m_possibleAnswers;
}

int Question::getCorrectAnswer()
{
    return this->correctIndex;
}

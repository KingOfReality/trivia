#include "GameRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include <iostream>
RequestResult GameRequestHandler::getQuestion(RequestInfo r)
{

    RequestResult req;

    ErrorRespone e;
    std::cout << "current questions sizeeeeee: " << this->m_game.getQuestions().size()<<std::endl;
    std::cout << "current getCurrentIndex : " << this->m_game.getCurrentIndex() << std::endl;
    if (this->m_game.getCurrentIndex() == this->m_game.getQuestions().size() )
    {
        e.message = "game over";
        req.Buffer = JsonResponsePacketSerializer::serializerRespone(e);
        req.newHandler = this;
        return req;
    }
    Question q = this->m_game.getCurrentQuestion();
    GetQuestionRespone g(q);
    g.status = 1;
   req.Buffer = JsonResponsePacketSerializer::serializerRespone(g);
   req.newHandler = this;
   return req;

}

RequestResult GameRequestHandler::submitAnswer(RequestInfo r)
{
    SubmitAnswerRequest s = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(r.v);
    SubmitAnswerRespone respone;
    
    respone.correctAnswerId = this->m_game.getCurrentQuestion().getCorrectAnswer();

    
        respone.status = this->m_game.submit(s.answerId);
    
   
    RequestResult res;
    res.newHandler = this;
    res.Buffer = JsonResponsePacketSerializer::serializerRespone(respone);
    return res;
}

RequestResult GameRequestHandler::getGameResult(RequestInfo r)
{
    PlayerResult p;
    std::cout << "the error is after this";
    p.correct = this->m_game.getCorrectAnswerCount();
    p.wrong = this->m_game.getWrongAnswerCount();
    p.avgTime = this->m_game.getAverageAnswerTime();
    p.username = this->m_user.getUsername();
    RequestResult res;

    res.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
    res.Buffer = JsonResponsePacketSerializer::serializerRespone(p);
    return res;
}

RequestResult GameRequestHandler::leaveGame(RequestInfo r)
{
    LeaveGameRespone l;
    l.status = 1;
    RequestResult res;
    this->m_gameManager.getSpec(this->m_game.getId()).games.erase(this->m_user.getUsername());

    res.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
    res.Buffer = JsonResponsePacketSerializer::serializerRespone(l);
    return res;
}

GameRequestHandler::GameRequestHandler(LoggedUser& l, RequestHandlerFactory& rhf, GameData& g)
    :m_handlerFactory(rhf), m_user(l),
    m_gameManager(rhf.getGameManager()), m_game(g)
{
}



bool GameRequestHandler::isRequestRelevant(RequestInfo r)
{
    if (r.id >= 40 && r.id < 44)
        return true;
    return false;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo r)
{
    ErrorRespone e;

  
    switch (r.id)
    {
    case 40:
        return getQuestion(r);
        break;

    case 41:
        return submitAnswer(r);
        break;

    case 42:
        return getGameResult(r);
        break;

    case 43:
        return leaveGame(r);
        break;

    
    }
}

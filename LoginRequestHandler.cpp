#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "json.hpp"
#include <string>
#include <iostream>
#include <bitset>
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
using json = nlohmann::json;

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& RHF) :m_handleFactory(RHF) {}


bool LoginRequestHandler::isRequestRelevant(RequestInfo r)
{
    return r.id == 1 || r.id == 2;
}


RequestResult LoginRequestHandler::handleRequest(RequestInfo r)
{
    ErrorRespone e;
    RequestResult requestResult;
    if (!this->isRequestRelevant(r))
    {
        e.message = "The code is not login or request!";
        requestResult.Buffer = JsonResponsePacketSerializer::serializerRespone(e);
        requestResult.newHandler = this->m_handleFactory.createLoginRequestHandler();
        return requestResult;
    }
    switch (r.id)
    {
    case 1: 
        return this->login(r);
        break;
    case 2:
        return this->signup(r);
        break;
    
    }

}

RequestResult LoginRequestHandler::login(RequestInfo r)
{
    ErrorRespone e;
    LoginRequest LG;
    LoginRespone loginRespone;
    RequestResult requestResult;
    json j;
    LG = JsonRequestPacketDeserializer::deserializeLoginRequest(r.v);
    if (this->m_handleFactory.getLoginManager().login(LG.username, LG.password) != true)
    {
        e.message = "Parameters dont match!";
        requestResult.Buffer = JsonResponsePacketSerializer::serializerRespone(e);
        requestResult.newHandler = this;
        return requestResult ;
    }
    std::cout << (LG.username, LG.password);
    loginRespone.status = 1;
    requestResult.Buffer = JsonResponsePacketSerializer::serializerRespone(loginRespone);
    requestResult.newHandler = this->m_handleFactory.createMenuRequestHandler(LoggedUser(LG.username));
    return requestResult;
}

RequestResult LoginRequestHandler::signup(RequestInfo r)
{
    ErrorRespone e;
    LoginManager l;
    SignupRequest SG;
    SignupRespone signupRespone;
    RequestResult requestResult;
    json j;
    SG = JsonRequestPacketDeserializer::deserializeSignupRequest(r.v);
    if (!this->m_handleFactory.getLoginManager().signup(SG.username,SG.password,SG.email))
    {
        e.message = "signup dont work!";
        requestResult.Buffer = JsonResponsePacketSerializer::serializerRespone(e);
        requestResult.newHandler = this->m_handleFactory.createLoginRequestHandler();

        return requestResult;
    }
    signupRespone.status = 1;
    requestResult.Buffer = JsonResponsePacketSerializer::serializerRespone(signupRespone);
    requestResult.newHandler = this->m_handleFactory.createLoginRequestHandler();
    return requestResult;
}

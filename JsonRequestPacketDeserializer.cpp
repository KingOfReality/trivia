#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
#include <iostream>

using json = nlohmann::json;
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> v)
{
    LoginRequest l;
    std::string str(v.begin(), v.end());
    json jsonObj = json::parse(str);
    l.password = jsonObj["password"];
    l.username = jsonObj["username"];

    return l;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> v)
{
    SignupRequest s;
    std::string str(v.begin(), v.end());
    json jsonObj = json::parse(str);
    s.password = jsonObj.at("password");
    s.username = jsonObj.at("username");
    s.email = jsonObj.at("email");
    return s;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(std::vector<unsigned char> v)
{
    GetPlayersInRoomRequest g;
    std::string str(v.begin(), v.end());
    json jsonObj = json::parse(str);
    g.roomId = jsonObj.at("roomId");
    return g;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<unsigned char> v)
{
    JoinRoomRequest j;
    std::string str(v.begin(), v.end());
    std::cout << str;
    json jsonObj = json::parse(str);
    j.roomId = jsonObj.at("roomId");
    return j;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<unsigned char> v)
{   
    CreateRoomRequest c;
    std::string str(v.begin(), v.end());
    json jsonObj = json::parse(str);
    c.answerTimeOut = jsonObj.at("timeOut");
    c.maxUsers = jsonObj.at("maxUsers");
    c.questionCount = jsonObj.at("questionCount");
    c.roomName = jsonObj.at("name");
    return c;
}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(std::vector<unsigned char> v)
{
    SubmitAnswerRequest s;
    std::string str(v.begin(), v.end());
    json jsonObj = json::parse(str);
    s.answerId = jsonObj.at("answer");

    return s;
}



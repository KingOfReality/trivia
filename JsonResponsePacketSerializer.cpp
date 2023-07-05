#include "JsonResponsePacketSerializer.h"
#include "json.hpp"
#include <bitset>
#include <iostream>
#define LOG_IN "00000001"
#define SIGN_UP "0000010"
#define LOG_OUT "00000100"
#define ERROR "00000011"

using json = nlohmann::json;
unsigned int stringToBinary(std::string input) {
    unsigned int binary = 0;
    unsigned int multiplier = 1;
    for (char& c : input) {
        binary += std::bitset<8>(c).to_ulong() * multiplier;
        multiplier *= 100000000;
    }
    return binary;
}

int convertToBinary(int n)
{
    unsigned int binaryNum = 0;
    unsigned int multiplier = 1;

    while (n > 0) {
        binaryNum += (n % 2) * multiplier;
        multiplier *= 10;
        n /= 2;
    }

    return binaryNum;
}
std::string intToBitString(int n) {
    std::bitset<32> bits(n); // Convert the int to a bitset
    return bits.to_string(); // Convert the bitset to a string of 32 bits
}

void pushStringToVector(std::string s, std::vector<unsigned char>& v)
{
    for (int i = 0; i < s.length(); i++)
        v.push_back(s[i]);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializerRespone(ErrorRespone e)
{
    json j;
    j["message"] = e.message;
    std::string json_string = j.dump();
    std::vector<unsigned char> vec(json_string.begin(), json_string.end());
    std::vector<unsigned char> v;
    pushStringToVector(ERROR, v);
    pushStringToVector(intToBitString(json_string.length()), v);
    v.insert(v.end(), vec.begin(), vec.end());

    return v;
}
std::vector<unsigned char> buildMsg(json j)
{
    std::string json_string = j.dump();
    std::vector<unsigned char> vec(json_string.begin(), json_string.end());
    std::vector<unsigned char> v;
    pushStringToVector(LOG_IN, v);
    pushStringToVector(intToBitString(json_string.length()), v);
    v.insert(v.end(), vec.begin(), vec.end());
        

    return v;
}
std::vector<unsigned char> JsonResponsePacketSerializer::serializerRespone(LoginRespone l)
{
    json j;
    j["status"] = l.status;
    return buildMsg(j);
   
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializerRespone(SignupRespone s)
{
    json j;
    j["status"] = s.status;
    return buildMsg(j);


}

std::vector<unsigned char> JsonResponsePacketSerializer::serializerRespone(LogOutRespone s)
{
    json j;
    j["status"] = s.status;
    return buildMsg(j);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializerRespone(GetRoomRespone s)
{
    std::vector<std::string> temp;
    json j;

    for (int i = 0; i < s.rooms.size(); i++)
    {
        j[s.rooms[i].name] = s.rooms[i].id;
    }
    return buildMsg(j);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializerRespone(GetPlayerInRoomRespone s)
{
    json j;
    j["Players"] = s.players;
    return buildMsg(j);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializerRespone(JoinRoomRespone s)
{
    json j;
    j["status"] = s.status;
    return buildMsg(j);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializerRespone(CreateRoomRespone s)
{
    json j;
    j["status"] = s.status;
    j["id"] = s.id;
    return buildMsg(j);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializerRespone(CloseRoomRespone s)
{
    json j;
    j["status"] = s.status;
    
    return buildMsg(j);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializerRespone(StartGameRespone s)
{
    json j;
    j["status"] = s.status;
    return buildMsg(j);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializerRespone(GetRoomStateRespone s)
{
    json j;
    std::cout << 55555555;

    j["status"] = s.status;
    j["gameBegun"] = s.gameBegun;
    j["players"] = s.players;
    j["count"] = s.questionCount;
    j["timeOut"] = s.answerTimeOut;
    return buildMsg(j);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializerRespone(LeaveRoomRespone s)
{
    json j;
    j["status"] = s.status;
    return buildMsg(j);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializerRespone(LeaveGameRespone s)
{
    json j;
    j["status"] = s.status;
    return buildMsg(j);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializerRespone(GetQuestionRespone s)
{
    json j;
    j["status"] = s.status;
    j["question"] = s.q.getQuestion();
    j["answers"] = s.q.getPossibleAnswers();
    j["correct"] = s.q.getCorrectAnswer();
    return buildMsg(j);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializerRespone(SubmitAnswerRespone s)
{
    json j; 
    j["correctIndex"] = s.correctAnswerId;
    j["status"] = s.status;
    return buildMsg(j);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializerRespone(PlayerResult s)
{
    json j;
    j["correctCount"] = s.correct;
    j["wrongCount"] = s.wrong;
    j["username"] = s.username;
    j["avg"] = s.avgTime;
    return buildMsg(j);
}

GetQuestionRespone::GetQuestionRespone(Question q):q(q)
{
    std::cout << std::endl << "the question: " << q.getQuestion() << std::endl;

}

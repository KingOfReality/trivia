#pragma once
#include <vector>
#include <string>
#include "Room.h"
#include "Question.h"
struct CloseRoomRespone
{
	unsigned int status;
};
struct StartGameRespone
{
	unsigned int status;
};
struct GetRoomStateRespone
{
	unsigned int status;
	bool gameBegun;
	std::vector<std::string> players;
	unsigned int questionCount;
	unsigned int answerTimeOut;
};
struct LeaveRoomRespone
{
	unsigned int status;
};
struct LogOutRespone
{
	unsigned int status;
}typedef;
struct GetRoomRespone
{
	unsigned int status;
	std::vector<RoomData> rooms;
};
struct GetPlayerInRoomRespone
{
	std::vector<std::string> players;
};
struct getHighScoreRespone
{
	unsigned int status;
	std::vector<std::string> statistics;
};
struct getPersonalStatsRespone
{
	unsigned int status;
	std::vector<std::string> s;
};
struct JoinRoomRespone
{
	unsigned int status;
};
struct  ErrorRespone
{
	 std::string message;
}typedef;

struct  LoginRespone
{
	 unsigned int status;

}typedef;

struct  SignupRespone
{
	 unsigned int status;
}typedef;

struct CreateRoomRespone
{
	 unsigned int status;
	 unsigned int id;
}typedef;

struct LeaveGameRespone
{
	unsigned int status;

};
struct GetQuestionRespone
{
	GetQuestionRespone(Question q);
	unsigned int status;
	Question q;

};

struct SubmitAnswerRespone
{
	unsigned int status;
	unsigned int correctAnswerId;

};
struct PlayerResult
{
	std::string username;
	unsigned int correct;
	unsigned int wrong;
	unsigned int avgTime;

};
class JsonResponsePacketSerializer
{
public: 
	static std::vector<unsigned char> serializerRespone(ErrorRespone e);
	static std::vector<unsigned char> serializerRespone(LoginRespone l);
	static std::vector<unsigned char> serializerRespone(SignupRespone s);
	static std::vector<unsigned char> serializerRespone(LogOutRespone s);
	static std::vector<unsigned char> serializerRespone(GetRoomRespone s);
	static std::vector<unsigned char> serializerRespone(GetPlayerInRoomRespone s);
	static std::vector<unsigned char> serializerRespone(JoinRoomRespone s);
	static std::vector<unsigned char> serializerRespone(CreateRoomRespone s);
	static std::vector<unsigned char> serializerRespone(CloseRoomRespone s);
	static std::vector<unsigned char> serializerRespone(StartGameRespone s);
	static std::vector<unsigned char> serializerRespone(GetRoomStateRespone s);
	static std::vector<unsigned char> serializerRespone(LeaveRoomRespone s);
	static std::vector<unsigned char> serializerRespone(LeaveGameRespone s);
	static std::vector<unsigned char> serializerRespone(GetQuestionRespone s);
	static std::vector<unsigned char> serializerRespone(SubmitAnswerRespone s);
	static std::vector<unsigned char> serializerRespone(PlayerResult s);

};
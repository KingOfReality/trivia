#pragma once
#include <vector>
#include <string>
struct LoginRequest
{
	 std::string username;
	 std::string password;

}typedef;
struct SubmitAnswerRequest
{
	unsigned int answerId;
};
struct SignupRequest
{
	std::string username;
	 std::string password;
	 std::string email;


}typedef;

struct  GetPlayersInRoomRequest
{
	unsigned int roomId;
}typedef;

struct  JoinRoomRequest
{
	unsigned int roomId;
}typedef;

struct  CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;

	unsigned int answerTimeOut;
}typedef;

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char> v);
	static SignupRequest deserializeSignupRequest(std::vector<unsigned char> v);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(std::vector<unsigned char> v);
	static JoinRoomRequest deserializeJoinRoomRequest(std::vector<unsigned char> v);
	static CreateRoomRequest deserializeCreateRoomRequest(std::vector<unsigned char> v);
	static SubmitAnswerRequest deserializeSubmitAnswerRequest(std::vector<unsigned char> v);
};
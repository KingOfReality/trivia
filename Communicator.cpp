#include "Communicator.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include <exception>
#include <iostream>
#include <thread>
#include <typeinfo>
#include "Helper.h"
#include <bitset>
#include <mutex>
#include <sstream>

std::mutex clients_mutex;
Communicator::Communicator(RequestHandlerFactory& r) : m_handlerFactory(r)
{
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Communicator::~Communicator()
{
	try
	{
		closesocket(_serverSocket);
	}
	catch (...) {}
}

void Communicator::serve(int port)
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(port);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;

	if (bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << port << std::endl;

	while (true)
	{
		std::cout << "Waiting for client connection request" << std::endl;
		acceptClient();
	}
}

void Communicator::acceptClient()
{
	SOCKET clientSocket = accept(_serverSocket, NULL, NULL);
	if (clientSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::cout << "Client accepted. Server and client can communicate" << std::endl;
	std::lock_guard<std::mutex> lock(clients_mutex);
	this->m_clients[clientSocket] = m_handlerFactory.createLoginRequestHandler();

	std::thread t(&Communicator::clientHandler, this, clientSocket);
	t.detach();
}

std::string stringToBinary(const std::string& str) {
	std::string binaryString;
	for (char c : str) {
		// Convert each character to its binary representation
		std::bitset<8> binary(c);
		binaryString += binary.to_string();
	}
	return binaryString;
}

int getDataLenFromHeader(char* pheader)
{
	char len[4] = { 0 };
	for (int i = 1; i < 5; i++)
		len[i - 1] = pheader[i];
	int a = static_cast<int>(static_cast<unsigned char>(len[0]) << 24 |
		static_cast<unsigned char>(len[1]) << 16 |
		static_cast<unsigned char>(len[2]) << 8 |
		static_cast<unsigned char>(len[3]));
	return a;
}
void recieve(SOCKET sock, char* data, int dataSize)
{
	int res = recv(sock, data, dataSize, 0);
	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sock);
		throw std::exception(s.c_str());
	}
}


std::string bytesToString(const unsigned char* bytes, size_t length) {
	return std::string(reinterpret_cast<const char*>(bytes), length);
}
void Communicator::clientHandler(SOCKET clientSocket)
{
	int name = 0;
	int length = 0;
	int type = 0;
	int msgLength = 255;
	std::string msg = "";
	RequestResult r;
	std::string requestResult;
	RequestInfo i;
	int res;
	std::string size;
	std::string strCode;
	char* header;
	char* data = nullptr;
	try
	{
		while (true)
		{
			 header = new char[5 + 1];
			recieve(clientSocket, header, 5);
			char code = (int)header[0];
			int lenOfData = getDataLenFromHeader(header);
			data = new char[lenOfData + 1];
			recieve(clientSocket, data, lenOfData);
			std::vector<unsigned char> result(data, data + lenOfData);
			std::vector<unsigned char> temp;
			i.id = (int)code;
			i.v = result;
			try {
				std::cout << std::endl << typeid(*this->m_clients[clientSocket]).name()<<std::endl<<i.id;

				 r = this->m_clients[clientSocket]->handleRequest(i);

				 requestResult = std::string(r.Buffer.begin(), r.Buffer.end());
			}
			catch
				(std::string e)
			{
				std::cout << e;
			}
				Helper::sendData(clientSocket, requestResult);
				this->m_clients[clientSocket] = r.newHandler;
		}
	}
	catch (const std::exception& e)
	{
		closesocket(clientSocket);
		std::cout << "Exception caught in clientHandler: " << e.what() << std::endl;
		// Handle the exception or take appropriate action
	}
}

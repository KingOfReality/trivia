#pragma once
#include <vector>
#include <ctime>
class IRequestHandler;
struct RequestInfo
{
	int id;
	std::vector<unsigned char> v;
};

struct RequestResult
{
	IRequestHandler* newHandler;
	std::vector<unsigned char> Buffer;
};
class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo r) = 0;
	virtual RequestResult handleRequest(RequestInfo r) = 0;
};
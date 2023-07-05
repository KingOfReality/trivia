#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;
struct RequestResult;
struct RequestInfo;
class MenuRequestHandler;
class LoginRequestHandler:public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory& RHF) ;
	bool isRequestRelevant(RequestInfo r);
	RequestResult handleRequest(RequestInfo r);
private:
	RequestHandlerFactory& m_handleFactory;
	RequestResult login(RequestInfo r);
	RequestResult signup(RequestInfo r);
};
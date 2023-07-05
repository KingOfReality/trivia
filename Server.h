#ifndef _SERVER
#define _SERVER
 // !_SERVER

#include "Communicator.h"
#include "IDatabase.h"
#include <iostream>
class RequestHandlerFactory;
class Commincator;
class SqliteDataBase;

class Server
{
private:
	IDatabase* m_database;
	RequestHandlerFactory m_handleFactory;
	Communicator m_communicator;
public:
	Server(RequestHandlerFactory& r,SqliteDataBase* sql);
	bool run();
};


#endif
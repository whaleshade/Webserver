#ifndef INFOCLIENT_HPP
#define INFOCLIENT_HPP

#include "InfoServer.hpp"
#include "../includes/cppLibrary.hpp"
#include "../includes/Define.hpp"
#include "../../parseRequest/Request.hpp"
#include "../response/Response.hpp"

class Request;

class InfoClient
{
	public:
		int _clientSocket;
		InfoServer *_server;
		std::string reqMsg;
		Request req;
		// Response res;

	public:
		InfoClient()
		: _clientSocket(-1), _server(nullptr), reqMsg("") {}
};


#endif

/***************************************************/
/* CODED BY JIN H. BANG ===========================*/
/***************************************************/

#ifndef INFOSERVER_HPP
#define INFOSERVER_HPP

#include "cppLibrary.hpp"

/* InfoServer *///-----------------------
class InfoServer
{
	public:
		int _serverSocket;
		std::string _ipAddress;
		int _port;
		struct sockaddr_in _serverAddr;
		unsigned int _serverAddrLen;
		std::string _requestMsg;
	public:
		InfoServer &operator=(InfoServer const &rhs)
		{
			_serverSocket = rhs._serverSocket;
			_ipAddress = rhs._ipAddress;
			_port = rhs._port;
			_serverAddr = rhs._serverAddr;
			_serverAddrLen = rhs._serverAddrLen;
			_requestMsg = rhs._requestMsg;
			return (*this);
		}
};

#endif

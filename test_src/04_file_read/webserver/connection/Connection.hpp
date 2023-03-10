/***************************************************/
/* CODED BY JIN H. BANG ===========================*/
/***************************************************/

#ifndef CONNECTION_HPP
#define CONNECTION_HPP


#include "../includes/Define.hpp"
#include "../includes/cppLibrary.hpp"

#include "../response/Response.hpp"
#include "Multiplex.hpp"
#include "InfoServer.hpp"
#include "InfoClient.hpp"

#include "../../parseRequest/Request.hpp"

class Connection
{
	private:
		// InfoServer _serverInfo;
		Multiplex _eventManager;
		// int _clientSocket;
	public:
		std::vector<int> _serverSockets;
		std::map<int, InfoServer> _serverMap;
		std::map<int, InfoClient> _clientMap;
		std::map<int, Response> _responserMap;
	public:
		std::string _clientReq;

	public:
		Connection();
		~Connection();
		void connectionLoop();

		class ConnectionError : public std::exception
		{
			public:
				const char *what() const throw() {
					return "Connection Error";
				}
		};
};

#endif

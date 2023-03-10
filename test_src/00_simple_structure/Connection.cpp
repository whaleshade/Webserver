/***************************************************/
/* CODED BY JIN H. BANG ===========================*/
/***************************************************/

#include "Connection.hpp"
#include "Define.hpp"
#include "Response.hpp"

class Response;

Connection::Connection()
{}

Connection::~Connection()
{}

void
Connection::connectionLoop(InfoServer &serverInfo)
{
	while (true)
	{
		_clientSocket = accept(serverInfo._serverSocket, (sockaddr *)&serverInfo._serverAddr, &serverInfo._serverAddrLen);
		if (_clientSocket == FAIL) {
			std::cerr << "Client connection error";

		}
		char buffer[BUFFER_SIZE] = {0,};
		int valRead = read(_clientSocket, buffer, BUFFER_SIZE);
		if (valRead == FAIL) {
			std::cerr << "Read error";
		}
		std::cout << "	from client : " << buffer << "\n";

		Response responser;
		responser.responseToClient(_clientSocket, serverInfo);
	}
}

/***************************************************/
/* CODED BY JIN H. BANG ===========================*/
/***************************************************/

#include "Response.hpp"

void
Response::responseToClient(int clientSocket, InfoClient infoClient)
{
	std::string resMsg = "";
	if (infoClient.req.t_result.method == GET)
	{
		resMsg = makeResponseGET(infoClient);
		std::cout << "		------result msg------- : \n" << resMsg << "\n";
	}
	else if (infoClient.req.t_result.method == POST)
	{
		char cwd[1024];
		getcwd(cwd, 1024);
		std::string cwdPath(cwd);
		std::string fullPath = cwdPath + "/www/cgi-bin/submit";
		std::string filePath = cwdPath + "/submit.html";
		int pid = fork();
		waitpid(pid, NULL, 0);
		if (pid == 0)
		{
			int fd = open(filePath.c_str(), O_WRONLY | O_CREAT, 0644);
			dup2(fd, STDOUT_FILENO);
			char **args = new char *[sizeof(char *) * 3];
			args[0] = strdup(fullPath.c_str());
			args[1] = strdup(infoClient.req.t_result.body.c_str());
			args[2] = NULL;
			execve(fullPath.c_str(), args, NULL);
		}
		else
		{
			resMsg = resMsgHeader(infoClient) + "\n" + resMsgBody(filePath);
			std::cout << " response to client : " << clientSocket << "\n";
			long valWrite = write(clientSocket, resMsg.c_str(), resMsg.size());
			if (valWrite == (long)resMsg.size())
				std::cout << "SERVER RESPONSE SENT\n";
			unlink(filePath.c_str());
			return ;
		}
	}
	else
	{
		resMsg = makeResponseERR();
	}

	(void)infoClient; // to be used

	std::cout << " response to client : " << clientSocket << "\n";
	long valWrite = write(clientSocket, resMsg.c_str(), resMsg.size());
	if (valWrite == (long)resMsg.size())
		std::cout << "SERVER RESPONSE SENT\n";
}

std::string
Response::makeResponseGET(InfoClient &infoClient)
{
	std::string resMsg;
	char cwd[1024];
	getcwd(cwd, 1024);
	std::string cwdPath(cwd);
	if (infoClient.req.t_result.target == "/home" || infoClient.req.t_result.target == "/")
		resMsg = resMsgHeader(infoClient) + "\n" + resMsgBody(cwdPath + "/resource/static/index.html");
	else if (infoClient.req.t_result.target == "/server")
		resMsg = resMsgHeader(infoClient) + "\n" + resMsgBody(cwdPath + "/resource/static/server.html");
	else if (infoClient.req.t_result.target == "/submit")
		resMsg = resMsgHeader(infoClient) + "\n" + resMsgBody(cwdPath + "/resource/static/submit.html");
	else
		resMsg = makeResponseERR();
	return (resMsg);
}

std::string
Response::makeResponseERR()
{
	std::stringstream httpRes;
	std::string htmlMsg = "HTTP/1.1 400 Not Found\nContent-Type: text/html; charset=utf-8\nContent-Length: 200\n\n<h1>ERROR</h1> <h2>404 NOT FOUND</h2>";
	return (htmlMsg);
}

std::string
Response::resMsgHeader(InfoClient &infoClient)
{
	std::stringstream header;
	(void)infoClient;
	setStatusCode(200);
	setStatusMsg(_statusMap[200]);
	setConnection("keep-alive");
	if (infoClient.req.t_result.close == true)
		setConnection("close");
	setContentType("text/html");
	// setTransferEncoding("chunked");
	setContentLength(1000);

	header << getHttpVersion() << " " << getStatusCode() << " " << getStatusMsg() << CRLF;
	header << "Content-Type: " << getContentType() << "; charset=utf-8" << CRLF;
	header << "Connection: " << getConnection() << CRLF;
	header << "Date: " << timeStamp() << CRLF;
	header << "Server: " << "little webserver" << CRLF;
	// header << "Transfer-Encoding : chunked" << CRLF;
	header << "Content-Length: " << getContentLength() << CRLF;

	return (header.str());
}

std::string
Response::resMsgBody(std::string srcLocation)
{
	std::stringstream body;
	_fileFd = open(srcLocation.c_str(), O_RDONLY);
	if (_fileFd == -1)
		std::cerr << "	ERROR: file open error\n";
	int valRead = read(_fileFd, _fileBuff, sizeof(_fileBuff));
	if (valRead == -1)
		std::cerr << "	ERROR: read\n";
	if (_fileFd == -1 || valRead == -1)
	{
		body << "<h1>ERROR</h1><img src=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAUAAAAFCAYAAACNbyblAAAAHElEQVQI12P4//8/w38GIAXDIBKE0DHxgljNBAAO9TXL0Y4OHwAAAABJRU5ErkJggg==\" alt=\"Red dot\" />";
	}
	else
		body << _fileBuff;

	return body.str();
}


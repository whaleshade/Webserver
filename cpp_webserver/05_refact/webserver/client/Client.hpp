#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../includes/libraries.hpp"
#include "../includes/Define.hpp"

#include "../server/Server.hpp"
#include "ResponseInfo.hpp"
#include "request/Request.hpp"
// #include "CGI.hpp"
#include "File.hpp"

class Client : public ResponseInfo
{
	public:
		int m_clientFd;
		Server *ptr_server;
		Request reqParser;
		bool isCgi;
		std::string m_resMsg;
		size_t m_totalBytes;
		size_t m_sentBytes;
		std::string cgiOutPath;
		std::string cgiOutTarget;

	public:
		int status;
		std::string path;

	public:
		FileEvent m_file;
		// CGI m_cgi;

	public:
		void openResponse();
		void openErrorResponse(int errorCode);
		void initResponse();
		void startResponse();
		void openfile(std::string targetPath);
		std::string getExecvePath();

	public:
		int sendResponse();
		size_t changePosition(int n);
		size_t getSendResultSize() const;
		const char * getSendResult() const;
		void clearResponseByte();
		char **initEnv(void);
		std::string cgiFinder(std::string target);
		int isValidTarget(std::string &target);
		int openDirectory(std::string &target);

	public:
		int writePipe(int fd);
		int	readFile(int fd);
		void clearFileEvent();


	public:
		Client()
		: m_clientFd(-1), ptr_server(NULL), status(0), path("") {}



	/* File */
	// public:
		// struct FileEvent
		// {
		// 	int fd;
		// 	std::size_t size;
		// 	std::string buffer;
		// 	std::size_t m_totalBytes;
		// 	std::size_t m_sentBytes;
		// 	std::size_t m_pipe_sentBytes;
		// 	int inFds[2];
		// 	int outFds[2];
		// 	int isFile;
		// 	std::string srcPath;
		// 	FileEvent() : fd(-1), size(0), buffer(""), m_totalBytes(0), m_sentBytes(0), m_pipe_sentBytes(0){}
		// };


};

#endif

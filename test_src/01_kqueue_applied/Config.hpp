/***************************************************/
/* CODED BY JIN H. BANG ===========================*/
/***************************************************/

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "Define.hpp"

class Config
{
	public:
		std::string ipAddr;
		int port;
	public:
		Config(std::string ipAddr, int port)
		: ipAddr(ipAddr), port(port) {}
};

#endif

#ifndef _UDP_SOCK_
#define _UDP_SOCK_

#include "WinSock.h"

class UDPSock : public WinSock
{
public:
	UDPSock();
	~UDPSock();

	WSReturn Open();
	void Close();

	WSReturn Send(const std::string &address, u_short port, const std::string &data);
	WSReturn Receive(u_long *address, u_short *port, std::string &buff);
};

#endif


#ifndef _TCP_SOCK_
#define _TCP_SOCK_

#include "WinSock.h"

class TCPSock : public WinSock
{
public:
	TCPSock();
	~TCPSock();

	WSReturn Open();
	void Close();

    WSReturn Listen();
    WSReturn Connect(const std::string &address, int port);
    TCPSock *Accept();

	WSReturn Send(const std::string &data);
	WSReturn Receive(std::string &buff);

private:
    TCPSock(SOCKET sock);

};

#endif



#ifndef _TCP_SOCK_
#define _TCP_SOCK_

#include "WinSock.h"

#include <vector>

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

	WSReturn Send(const std::vector<char> &data);
	WSReturn Receive(std::vector<char> &buff);

private:
    TCPSock(SOCKET sock);

};

#endif



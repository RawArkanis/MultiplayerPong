#ifndef _WIN_SOCK_
#define _WIN_SOCK_

#include <winsock2.h>
#include <ws2tcpip.h>

#include <iostream>
#include <string>

enum WSReturn
{
	WS_OK,
	WS_ERR_WSA_STARTUP,
	WS_ERR_WSA_CLEANUP,
	WS_ERR_SOCKET,
	WS_ERR_BIND,
    WS_ERR_LISTEN,
    WS_ERR_CONNECT,
    WS_ERR_ACCEPT,
	WS_ERR_SOCKOPT,
	WS_ERR_SOCKIOMODE,
	WS_ERR_ALREADY_OPEN,
	WS_ERR_NOT_OPEN,
    WS_ERR_NOT_ACCEPTED,
    WS_ERR_INET_PTON,
    WS_ERR_WOULDBLOCK,
    WS_ERR_SEND,
	WS_ERR_RECV
};

const u_int MAX_BUFF_SIZE = 512;

class WinSock
{
protected:
	static int _instanceCount;
	bool _isOpen;
	SOCKET _socket;

public:
	WinSock();
	~WinSock();

	WSReturn Initialize();
	WSReturn Destroy();

    bool IsOpen();
	int GetLastError();

	virtual WSReturn Open();
	virtual void Close();

	WSReturn Bind(u_short port);
	
	WSReturn SetOption(int level, int name, int value, int len);
	WSReturn SetIOMode(long cmd, u_long value);
};

#endif


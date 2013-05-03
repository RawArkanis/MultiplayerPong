#include "WinSock.h"

int WinSock::_instanceCount = 0;

WinSock::WinSock()
	: _isOpen(false),
	_socket(NULL)
{
}

WinSock::~WinSock()
{
    if (!_socket)
        Close();

    if (_instanceCount == 0)
		Destroy();
}

WSReturn WinSock::Initialize()
{
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
		return WS_ERR_WSA_STARTUP;
	
	std::cout << "WSA initialized" << std::endl;

	return WS_OK;
}

WSReturn WinSock::Destroy()
{
	if (WSACleanup() != 0)
		return WS_ERR_WSA_CLEANUP;
	
	std::cout << "WSA destroyed" << std::endl;

	return WS_OK;
}

bool WinSock::IsOpen()
{
    return _isOpen;
}

int WinSock::GetLastError()
{
	return WSAGetLastError();
}

WSReturn WinSock::Open()
{
	return WS_OK;
}

void WinSock::Close()
{
}

WSReturn WinSock::Bind(u_short port)
{
	if (!_isOpen)
		return WS_ERR_NOT_OPEN;

	SOCKADDR_IN sin;

	sin.sin_family = AF_INET; 
	sin.sin_addr.s_addr = INADDR_ANY; 
	sin.sin_port = htons(port);

	if(bind(_socket, (LPSOCKADDR)&sin, sizeof(sin)) != 0)
	   return WS_ERR_BIND;

	return WS_OK;
}

WSReturn WinSock::SetOption(int level, int name, int value, int len)
{
	if (!_isOpen)
		return WS_ERR_NOT_OPEN;

	char c = value;
	if(setsockopt(_socket, level, name, &c, len) != 0)
	   return WS_ERR_SOCKOPT;

	return WS_OK;
}

WSReturn WinSock::SetIOMode(long cmd, u_long value)
{
	if (!_isOpen)
		return WS_ERR_NOT_OPEN;

	if(ioctlsocket(_socket, cmd, &value) != 0)
		return WS_ERR_SOCKIOMODE;

	return WS_OK;
}

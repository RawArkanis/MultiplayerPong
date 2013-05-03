#include "TCPSock.h"

TCPSock::TCPSock()
    : WinSock()
{
}

TCPSock::TCPSock(SOCKET sock)
    : WinSock()
{
    _socket = sock;
    _isOpen = true;
}

TCPSock::~TCPSock()
{
}

WSReturn TCPSock::Open()
{
	if (_isOpen)
		return WS_ERR_ALREADY_OPEN;

    if (_instanceCount == 0)
        Initialize();

	if((_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	   return WS_ERR_SOCKET;

    _instanceCount++;
	_isOpen = true;

	std::cout << "Socket opened" << std::endl;
	std::cout << "Instance Count = " << _instanceCount << std::endl;

	return WS_OK;
}

void TCPSock::Close()
{
    if (_isOpen)
	{
		closesocket(_socket);
		_socket = NULL;

		_instanceCount--;
		_isOpen = false;

		if (_instanceCount == 0)
			Destroy();

		std::cout << "Socket closed" << std::endl;
		std::cout << "Instance Count = " << _instanceCount << std::endl;
    }
}

WSReturn TCPSock::Listen()
{
    if (!_isOpen)
		return WS_ERR_NOT_OPEN;

    if (listen(_socket, 5) == SOCKET_ERROR)
        return WS_ERR_LISTEN;

    return WS_OK;
}

WSReturn TCPSock::Connect(const std::string &address, int port)
{
    if (!_isOpen)
		return WS_ERR_NOT_OPEN;

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port); 

    if (inet_pton(AF_INET, address.c_str(), &addr.sin_addr) <= 0)
        return WS_ERR_INET_PTON;

    if (connect(_socket, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
        return WS_ERR_CONNECT;

    return WS_OK;
}

TCPSock *TCPSock::Accept()
{
    if (!_isOpen)
		return nullptr;

    SOCKET s = accept(_socket, (struct sockaddr*)NULL, NULL); 

    if(s != INVALID_SOCKET)
        return new TCPSock(s);

    return nullptr;
}

WSReturn TCPSock::Send(const std::string &data)
{
	if (!_isOpen)
		return WS_ERR_NOT_OPEN;

    if(send(_socket, data.c_str(), data.length() + 1, 0) != SOCKET_ERROR)
    {
        std::cout << "Information sent" << std::endl;
        return WS_OK;
    }

    return (WSAGetLastError() == WSAEWOULDBLOCK) ? WS_ERR_WOULDBLOCK : WS_ERR_SEND;
}

WSReturn TCPSock::Receive(std::string &buff)
{
	if (!_isOpen)
		return WS_ERR_NOT_OPEN;

	char temp[MAX_BUFF_SIZE];
	int len;

	if((len = recv(_socket, temp, MAX_BUFF_SIZE, 0)) != SOCKET_ERROR)
	{
		buff = std::string(temp);

		std::cout << "Information received" << std::endl;

		return WS_OK;
	}

	return WS_ERR_RECV;
}

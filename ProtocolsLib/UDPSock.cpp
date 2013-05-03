#include "UDPSock.h"

UDPSock::UDPSock()
	: WinSock()
{
}

UDPSock::~UDPSock()
{
}

WSReturn UDPSock::Open()
{
	if (_isOpen)
		return WS_ERR_ALREADY_OPEN;

    if (_instanceCount == 0)
        Initialize();

	if((_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	   return WS_ERR_SOCKET;

    _instanceCount++;
	_isOpen = true;

	std::cout << "Socket opened" << std::endl;
	std::cout << "Instance Count = " << _instanceCount << std::endl;

	return WS_OK;
}

void UDPSock::Close()
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

WSReturn UDPSock::Send(const std::string &address, u_short port, const std::string &data)
{
	if (!_isOpen)
		return WS_ERR_NOT_OPEN;

    SOCKADDR_IN sin;

    sin.sin_family = AF_INET; 
	sin.sin_addr.S_un.S_addr = inet_addr(address.c_str()); 
    sin.sin_port = htons(port);

    if(sendto(_socket, data.c_str(), data.length() + 1, 0, (LPSOCKADDR)&sin, sizeof(sin)) != SOCKET_ERROR)
    {
        std::cout << "Information sent" << std::endl;
        return WS_OK;
    }

    return (WSAGetLastError() == WSAEWOULDBLOCK) ? WS_ERR_WOULDBLOCK : WS_ERR_SEND;
}

WSReturn UDPSock::Receive(u_long *address, u_short *port, std::string &buff)
{
	if (!_isOpen)
		return WS_ERR_NOT_OPEN;

	SOCKADDR_IN from;
	int fromLen;

	char temp[MAX_BUFF_SIZE];
	int len;

	fromLen = sizeof(from);
	if((len = recvfrom(_socket, temp, MAX_BUFF_SIZE, 0, (LPSOCKADDR)&from, &fromLen)) != SOCKET_ERROR)
	{
		buff = std::string(temp);

		if( address != NULL )
			*address = ntohl(from.sin_addr.s_addr);
		if( port != NULL )
			*port = ntohs(from.sin_port);

		std::cout << "Information received" << std::endl;

		return WS_OK;
	}

	return WS_ERR_RECV;
}


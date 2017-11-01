/*
 * Copyright (C) 2017 by Godlike
 * This code is licensed under the MIT license (MIT)
 * (http://opensource.org/licenses/MIT)
 */
/* Original story "Networking for Game Programmers" by Glenn Fiedler
 */

#include <pony/Address.hpp>
#include <pony/Socket.hpp>

#if !defined(_WIN32)
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

namespace pony
{

bool SocketsInit()
{
#if defined(_WIN32)
    WSADATA WsaData;
    return (WSAStartup(MAKEWORD(2,2), &WsaData) == 0);
#else
    return true;
#endif
}

void SocketsKill()
{
#if defined(_WIN32)
    WSACleanup();
#endif
}

Socket::Socket() : m_socket(0) {}

Socket::~Socket()
{
    Close();
}

bool Socket::IsOpen() const
{
    return (m_socket > 0);
}

void Socket::Close()
{
    if (!m_socket)
	return;
#if defined(_WIN32)
    closesocket(m_socket);
#else
    close(m_socket);
#endif
    m_socket = 0;
}

bool Socket::Open(unsigned short port)
{
    if ((m_socket != 0) || (port <= 0))
	return false;

    m_socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_socket <= 0) {
	m_socket = 0;
	return false;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(m_socket, (const sockaddr *)&address, sizeof(sockaddr_in)) < 0) {
        Close();
        return false;
    }

#if defined(_WIN32)
    DWORD nonBlocking = 1;
    if (ioctlsocket(m_socket, FIONBIO, &nonBlocking) != 0) {
#else
    int nonBlocking = 1;
    if (fcntl(m_socket, F_SETFL, O_NONBLOCK, nonBlocking) == -1) {
#endif
        Close();
        return false;
    }

    return true;
}

signed Socket::Send(const Address& dst, const void* data, unsigned size)
{
    if ((m_socket == 0) || (!data) || (size <= 0))
        return -1;

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(dst.GetAddress());
    address.sin_port = htons(dst.GetPort());

    unsigned sended = sendto(m_socket, data, size, 0, (sockaddr *) &address, sizeof(sockaddr_in));
    if (size - sended)
        return 0;

    return sended;
}

signed Socket::Recv(Address& sender, void* data, unsigned size)
{
    if ((m_socket == 0) || (!data) || (size <= 0))
        return -1;

    sockaddr_in from;
#if defined(_WIN32)
    typedef int socklen_t;
#endif
    socklen_t fromLength = sizeof(from);

    int received = recvfrom(m_socket, data, size, 0, (sockaddr *) &from, &fromLength);
    if (received <= 0)
        return 0;

    unsigned int address = ntohl(from.sin_addr.s_addr);
    unsigned short port = ntohs(from.sin_port);

    sender = Address(address, port);

    return received;
}

}

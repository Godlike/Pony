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

using namespace pony;

bool pony::InitSockets()
{
#if defined(_WIN32)
    WSADATA WsaData;
    return (WSAStartup(MAKEWORD(2,2), &WsaData) == 0);
#else
    return true;
#endif
}

void pony::DeinitSockets()
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
    return (0 < m_socket);
}

void Socket::Close()
{
    if (!m_socket)
    {
	return;
    }
#if defined(_WIN32)
    closesocket(m_socket);
#else
    close(m_socket);
#endif
    m_socket = 0;
}

bool Socket::Open(uint16_t port)
{
    if (m_socket || (!port))
    {
        return false;
    }

    m_socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (0 >= m_socket)
    {
        m_socket = 0;
        return false;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (0 > bind(m_socket, reinterpret_cast<const sockaddr*> (&address), sizeof(sockaddr_in)))
    {
        Close();
        return false;
    }

#if defined(_WIN32)
    DWORD nonBlocking = 1;
    if (ioctlsocket(m_socket, FIONBIO, &nonBlocking) != 0)
#else
    int nonBlocking = 1;
    if (fcntl(m_socket, F_SETFL, O_NONBLOCK, nonBlocking) == -1)
#endif
    {
        Close();
        return false;
    }

    return true;
}

int32_t Socket::Send(Address destination, const void* data, uint32_t size)
{
    if ((!m_socket) || (!data) || (!size))
    {
        return -1;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(destination.GetAddress());
    address.sin_port = htons(destination.GetPort());

    uint32_t sent = sendto(m_socket,
                           reinterpret_cast<const char*> (data),
                           size,
                           0,
                           reinterpret_cast<sockaddr*> (&address),
                           sizeof(sockaddr_in));
    if (size - sent)
    {
        return 0;
    }

    return sent;
}

int32_t Socket::Receive(Address& sender, void* data, uint32_t size)
{
    if ((!m_socket) || (!data) || (!size))
    {
        return -1;
    }

    sockaddr_in from;
#if defined(_WIN32)
    typedef int32_t socklen_t;
#endif
    socklen_t fromLength = sizeof(from);

    int32_t received = recvfrom(m_socket,
                                reinterpret_cast<char*> (data),
                                size,
                                0,
                                reinterpret_cast<sockaddr*> (&from),
                                &fromLength);
    if (0 >= received)
    {
        return 0;
    }

    const uint32_t address = ntohl(from.sin_addr.s_addr);
    const uint16_t port = ntohs(from.sin_port);


    sender = Address(port, address);

    return received;
}

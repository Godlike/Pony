/*
 * Copyright (C) 2017 by Godlike
 * This code is licensed under the MIT license (MIT)
 * (http://opensource.org/licenses/MIT)
 */
/* Original story "Networking for Game Programmers" by Glenn Fiedler
 */

#include <pony/Address.hpp>
#include <pony/Socket.hpp>

#if defined(_WIN32)
	#include <winsock2.h>
	#pragma comment( lib, "ws2_32.lib" )
	#pragma warning( disable : 4996  ) // get rid of all secure crt warning. (sscanf_s)
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <sys/types.h>
	#include <netinet/in.h>
	#include <unistd.h>
	#include <fcntl.h>
#endif

namespace pony
{

#if defined(_WIN32)
void wait_seconds(float seconds) {
    Sleep((int)(seconds * 1000.0f));
}
#else
#include <unistd.h>
void wait_seconds(float seconds) {
    usleep((int)(seconds * 1000000.0f));
}
#endif

Socket::Socket() : m_socket(0) {}

bool Socket::IsOpen() const
{
    return m_socket > 0;
}

void Socket::Close()
{
    if ( ! m_socket)
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
    address.sin_port = htons((unsigned short) port);

    if (bind(m_socket, (const sockaddr *)&address, sizeof(sockaddr_in)) < 0) {
        Close();
        return false;
    }

#if defined(_WIN32)
    DWORD nonBlocking = 1;
    if (ioctlsocket( socket, FIONBIO, &nonBlocking) != 0) {
	printf( "failed to set non-blocking socket\n" );
	Close();
	return false;
    }
#else
    int nonBlocking = 1;
    if (fcntl(m_socket, F_SETFL, O_NONBLOCK, nonBlocking) == -1) {
        Close();
        return false;
    }
#endif
    return true;
}

int Socket::Send(const Address & dst, const void * data, unsigned size)
{
    if ((m_socket == 0) || ( ! data) || (size <=0))
        return -1;

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(dst.GetAddress());
    address.sin_port        = htons((unsigned short) dst.GetPort());

    int sended_bytes = sendto(m_socket, (const char*)data, size, 0, (sockaddr*)&address, sizeof(sockaddr_in));
    if (size - sended_bytes)
        return 0;

    return sended_bytes;
}

int Socket::Recv(Address & sender, void * data, unsigned size)
{
    if ((m_socket == 0) || ( ! data) || (size <=0))
        return -1;

    sockaddr_in from;
#if defined(_WIN32)
	typedef int socklen_t;
#endif
    socklen_t fromLength = sizeof(from);

    int received_bytes = recvfrom(m_socket, (char*)data, size, 0, (sockaddr*)&from, &fromLength);
    if (received_bytes <= 0)
        return 0;

    unsigned int address = ntohl(from.sin_addr.s_addr);
    unsigned int port = ntohs(from.sin_port);
    sender = Address(address, port);

    return received_bytes;
}

}

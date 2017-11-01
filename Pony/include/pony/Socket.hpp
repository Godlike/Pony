/*
 * Copyright (C) 2017 by Godlike
 * This code is licensed under the MIT license (MIT)
 * (http://opensource.org/licenses/MIT)
 */
/* Original story "Networking for Game Programmers" by Glenn Fiedler
 */

#ifndef PONY_SOCKET_HPP
#define PONY_SOCKET_HPP

#include <pony/Address.hpp>

#if defined(_WIN32)
    #include <winsock2.h>
//    #pragma comment( lib, "ws2_32.lib" )
#endif

namespace pony
{

bool SocketsInit();

void SocketsKill();

/**
 * @brief BSD Socket wrapper
 */
class Socket
{
public:
    Socket();
    ~Socket();

    bool IsOpen() const;

    bool Open(unsigned short port);
    void Close();

    signed Send(const Address& dst, const void* data, unsigned size);
    signed Recv(Address& sender, void* data, unsigned size);

protected:
private:
#if defined(_WIN32)
    SOCKET
#else
    signed
#endif
    m_socket;
};

} // namespace pony

#endif // PONY_SOCKET_HPP

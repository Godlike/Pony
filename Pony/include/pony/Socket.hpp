/*
 * Copyright (C) 2017 by Godlike
 * This code is licensed under the MIT license (MIT)
 * (http://opensource.org/licenses/MIT)
 */
/* Original story "Networking for Game Programmers" by Glenn Fiedler
 */

#ifndef ___PONY__SOCKET_HPP___
#define ___PONY__SOCKET_HPP___

#include <pony/Address.hpp>

#if defined(_WIN32)
    #include <winsock2.h>
    #pragma comment( lib, "ws2_32.lib" )
#endif

namespace pony
{

///HACK: to make Winsock happy we need in socketInit()/Kill()!
inline bool socketsInit()
{
#if defined(_WIN32)
    WSADATA WsaData;
    return (WSAStartup(MAKEWORD(2,2), &WsaData) == 0);
#else
    return true;
#endif
}

inline void socketsKill()
{
#if defined(_WIN32)
    WSACleanup();
#endif
}

/**
 * @brief BSD Socket wrapper
 */
class Socket
{
public:
    Socket();
    ~Socket();

    bool IsOpen() const;

    bool Open(const unsigned short port);
    void Close();

    int Send(const Address & dst, const void * const data, const unsigned size);
    int Recv(Address & sender, void * data, unsigned size);

protected:
private:
#if defined(_WIN32)
    SOCKET
#else
    signed
#endif
    m_socket;
};

} // namespacew Pony

#endif // ___PONY__SOCKET_HPP___

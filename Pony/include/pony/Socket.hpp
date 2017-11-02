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
#endif

namespace pony
{

bool SocketsInit();

void SocketsKill();

class Socket
{
public:
    Socket();
    ~Socket();

    bool IsOpen() const;

    bool Open(uint16_t port);
    void Close();

    int32_t Send(const Address& destination, const void* data, uint32_t size);
    int32_t Received(Address& sender, void* data, uint32_t size);
protected:
private:
#if defined(_WIN32)
    SOCKET
#else
    int32_t
#endif
    m_socket;
};

} // namespace pony

#endif // PONY_SOCKET_HPP

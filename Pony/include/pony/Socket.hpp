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

bool InitSockets();

void DeinitSockets();

class Socket
{
public:
    Socket();
    ~Socket();

    bool IsOpen() const;

    bool Open(uint16_t port);
    void Close();

    int32_t Send(Address destination, const void* data, uint32_t size);
    int32_t Receive(Address& sender, void* data, uint32_t size);
private:
#if defined(_WIN32)
    SOCKET m_socket;
#else
    int32_t m_socket;
#endif
};

} // namespace pony

#endif // PONY_SOCKET_HPP

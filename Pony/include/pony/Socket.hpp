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
///@note: InitSockets() should be call once
/// in the start of code that uses Sockets
///@note: for Windows compatible
bool InitSockets();
///@note: InitSockets() should be call once
/// in the end of code that uses Sockets
///@note: for Windows compatible
void DeinitSockets();
/**
@class Socket
  Socket class wraps BSD sockets. Socket class consist of constructor,
destructor, initialization methods (Open, Close), and data trtansition methods
(Send, Receive).
*/
class Socket
{
public:
    ///Construcor
    Socket();
    ///Destructor
    ~Socket();
    ///validation method (check is socket valid and is port assigned)
    ///@return true if ok, otherwise false
    bool IsOpen() const;
    ///Open - routine to assign the port to the socket
    ///@param number of port
    ///@return true if the port was assign to the socket properlly,
    /// otherwise false
    bool Open(uint16_t port);
    ///Close - release socket handler
    void Close();
    ///Send method send chunk of data with size to destination address
    ///@param destination - destination address
    ///@param data - point to chunck of data
    ///@param size - size of chunck of data
    ///@return -1 if input validation failure, 0 if error or
    /// size of sent data
    int32_t Send(Address destination, const void* data, uint32_t size);
    ///Receive method receiv chunk of data with size from sender
    ///@param sender - source adddress
    ///@param data - pointer to buffer for received data
    ///@param size - size of buffer for received data
    ///@return -1 if input validation failure, 0 if error or
    /// size of received data
    int32_t Receive(Address& sender, void* data, uint32_t size);
private:
    /// Handler
#if defined(_WIN32)
    SOCKET m_socket;
#else
    int32_t m_socket;
#endif
};

} // namespace pony

#endif // PONY_SOCKET_HPP

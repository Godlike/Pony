/*
 * Copyright (C) 2017 by Godlike
 * This code is licensed under the MIT license (MIT)
 * (http://opensource.org/licenses/MIT)
 */
/* Original story "Networking for Game Programmers" by Glenn Fiedler
 */

#ifndef PONY_SOCKET_HPP
#define PONY_SOCKET_HPP

namespace pony
{

class Socket
{

public:
    Socket();

    void Close();
    bool Open(unsigned short port);
    bool IsOpen() const;

    int Send(const Address & dst, const void * data, unsigned size);
    int Receive(Address & sender, void * data, unsigned size);

protected:

private:
    signed m_socket;

};

}

#endif // PONY_SOCKET_HPP

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
#include <pony/SharedMacros.hpp>

namespace pony
{

class PONY_EXPORT Socket
{

public:
    Socket();

    bool IsOpen() const;

    bool Open(unsigned short port);
    void Close();

    int Send(const Address & dst, const void * data, unsigned size);
    int Recv(Address & sender, void * data, unsigned size);

protected:

private:
    signed m_socket;

};

}

#endif // PONY_SOCKET_HPP

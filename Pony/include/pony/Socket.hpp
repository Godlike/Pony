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

class Socket
{

public:
    PONY_EXPORT Socket();

    PONY_EXPORT bool IsOpen() const;

    PONY_EXPORT bool Open(unsigned short port);
    PONY_EXPORT void Close();

    PONY_EXPORT int Send(const Address & dst, const void * data, unsigned size);
    PONY_EXPORT int Receive(Address & sender, void * data, unsigned size);

protected:

private:
    signed m_socket;

};

}

#endif // PONY_SOCKET_HPP

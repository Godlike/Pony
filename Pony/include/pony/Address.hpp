/*
 * Copyright (C) 2017 by Godlike
 * This code is licensed under the MIT license (MIT)
 * (http://opensource.org/licenses/MIT)
 */
/* Original story "Networking for Game Programmers" by Glenn Fiedler
 */

#ifndef PONY_ADDRESS_HPP
#define PONY_ADDRESS_HPP

#include <pony/SharedMacros.hpp>

namespace pony
{

class Address
{

public:
    PONY_EXPORT Address();
    PONY_EXPORT Address(unsigned int address);
    PONY_EXPORT Address(unsigned int address, unsigned short port);
    PONY_EXPORT Address(unsigned char fst, unsigned char snd, unsigned char thd, unsigned char fth, unsigned short port);

    PONY_EXPORT unsigned int GetAddress() const;
    PONY_EXPORT unsigned short GetPort() const;

    PONY_EXPORT const bool operator == (const Address & rhs);
    PONY_EXPORT const bool operator != (const Address & rhs);

protected:

private:
    unsigned int m_address;
    unsigned short m_port;

};

}

#endif//PONY_ADDRESS_HPP

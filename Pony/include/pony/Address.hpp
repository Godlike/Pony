/*
 * Copyright (C) 2017 by Godlike
 * This code is licensed under the MIT license (MIT)
 * (http://opensource.org/licenses/MIT)
 */
/* Original story "Networking for Game Programmers" by Glenn Fiedler
 */

#ifndef PONY_ADDRESS_HPP
#define PONY_ADDRESS_HPP

namespace pony
{

class Address
{

public:
    Address();
    Address(unsigned int address);
    Address(unsigned int address, unsigned short port);
    Address(unsigned char fst, unsigned char snd, unsigned char thd, unsigned char fth, unsigned short port);

    unsigned int GetAddress() const;
    unsigned short GetPort() const;

    const bool operator == (const Address & rhs);
    const bool operator != (const Address & rhs);

protected:

private:
    unsigned int m_address;
    unsigned short m_port;

};

}

#endif//PONY_ADDRESS_HPP

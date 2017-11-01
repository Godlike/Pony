/*
 * Copyright (C) 2017 by Godlike
 * This code is licensed under the MIT license (MIT)
 * (http://opensource.org/licenses/MIT)
 */
/* Original story "Networking for Game Programmers" by Glenn Fiedler
 */

#include <pony/Address.hpp>

namespace pony
{

Address::Address() : m_address(0), m_port(0) {}

Address::Address(unsigned address) : m_address(address), m_port(0) {}

Address::Address(unsigned address, unsigned short port) : m_address(address), m_port(port) {}

Address::Address(unsigned char fst, unsigned char snd, unsigned char thd, unsigned char fth, unsigned short port) : m_address(fth), m_port(port)
{
    m_address |= ((thd << 8) | (snd << 16) | (fst << 24));
}

unsigned Address::GetAddress() const
{
    return m_address;
}

unsigned char Address::GetFst() const
{
    return (m_address >> 24);
}

unsigned char Address::GetSnd() const
{
    return (m_address >> 16);
}

unsigned char Address::GetThd() const
{
    return (m_address >>  8);
}

unsigned char Address::GetFth() const
{
    return m_address;
}

unsigned short Address::GetPort() const
{
    return m_port;
}

bool Address::operator== (const Address& rhs) const
{
    return (m_address == rhs.GetAddress() && m_port == rhs.GetPort());
}

bool Address::operator!= (const Address& rhs) const
{
    return !(*this == rhs);
}

}

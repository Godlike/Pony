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

Address::Address(uint32_t address) : m_address(address), m_port(0) {}

Address::Address(uint32_t address, uint16_t port) : m_address(address), m_port(port) {}

Address::Address(uint8_t fst, uint8_t snd, uint8_t thd, uint8_t fth, uint16_t port) : m_address(fth), m_port(port)
{
    m_address |= ((thd << 8) | (snd << 16) | (fst << 24));
}

uint32_t Address::GetAddress() const
{
    return m_address;
}

uint8_t Address::GetAddressPart(uint32_t nr) const
{
    return (m_address >> (32 - 8 * nr));
}

uint16_t Address::GetPort() const
{
    return m_port;
}

bool Address::operator== (Address rhs) const
{
    return (m_address == rhs.GetAddress() && m_port == rhs.GetPort());
}

bool Address::operator!= (Address rhs) const
{
    return !(*this == rhs);
}

}

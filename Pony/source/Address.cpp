/*
 * Copyright (C) 2017 by Godlike
 * This code is licensed under the MIT license (MIT)
 * (http://opensource.org/licenses/MIT)
 */
/* Original story "Networking for Game Programmers" by Glenn Fiedler
 */

#include <pony/Address.hpp>

using namespace pony;

Address::Address(uint16_t port, uint32_t address) : m_port(port), m_address(address) {}

uint32_t Address::GetAddress() const
{
    return m_address;
}

uint16_t Address::GetPort() const
{
    return m_port;
}

bool Address::operator== (const Address& rhs) const
{
    return ((m_address == rhs.GetAddress()) && (m_port == rhs.GetPort()));
}

bool Address::operator!= (const Address& rhs) const
{
    return !(operator==(rhs));
}

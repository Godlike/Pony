/*
 * Copyright (C) 2017 by Godlike
 * This code is licensed under the MIT license (MIT)
 * (http://opensource.org/licenses/MIT)
 */
/* Original story "Networking for Game Programmers" by Glenn Fiedler
 */

#ifndef PONY_ADDRESS_HPP
#define PONY_ADDRESS_HPP

#include <cstdint>

namespace pony
{

class Address
{
public:
    Address(uint16_t port = 0, uint32_t address = 0);

    uint32_t GetAddress() const;
    uint16_t GetPort() const;

    bool operator== (const Address& rhs) const;
    bool operator!= (const Address& rhs) const;
private:
    uint16_t m_port;
    uint32_t m_address;
};

} // namespace pony

#endif // PONY_ADDRESS_HPP

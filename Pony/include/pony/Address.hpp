/*
 * Copyright (C) 2017 by Godlike
 * This code is licensed under the MIT license (MIT)
 * (http://opensource.org/licenses/MIT)
 */
/* Original story "Networking for Game Programmers" by Glenn Fiedler
 */

#ifndef PONY_ADDRESS_HPP
#define PONY_ADDRESS_HPP

#include <stdint.h>

namespace pony
{

class Address
{
public:
    Address();
    Address(uint32_t address);
    Address(uint32_t address, uint16_t port);
    Address(uint8_t fst, uint8_t snd, uint8_t thd, uint8_t fth, uint16_t port);

    uint32_t GetAddress() const;
    uint16_t GetPort() const;

    uint8_t GetAddressPart(uint32_t nr) const;

    bool operator == (const Address& rhs) const;
    bool operator != (const Address& rhs) const;

protected:
private:
    uint32_t m_address;
    uint16_t m_port;
};

} // namespace pony

#endif // PONY_ADDRESS_HPP

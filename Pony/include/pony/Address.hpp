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
/**
@class Address
  Address class implements addressing within IP network uses IP version 4.
Address class consist of constructor, access methods and equality operators.
*/
class Address
{
public:
    ///constructor
    ///@note: by default port should be equal = ??? and address = 127.0.0.1
    ///@note: if address is using, port should be used as well
    Address(uint16_t port = 0, uint32_t address = ((127 << 24) | (0 << 16) | (0 << 8) | 1));
    ///GetPort access methode
    ///@return port
    uint16_t GetPort() const;
    ///GetAddress access methode
    ///@return address
    uint32_t GetAddress() const;

    bool operator== (const Address& rhs) const;
    bool operator!= (const Address& rhs) const;
private:
    /// Application port
    uint16_t m_port;
    /// IP address
    uint32_t m_address;
};

} // namespace pony

#endif // PONY_ADDRESS_HPP

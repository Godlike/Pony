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
/**
 * @brief Address
 *
 * Adderss - abstraction of IP Address + UDP Port.
 */
class Address
{
public:
    Address();
    Address(unsigned address);
    Address(unsigned address, unsigned short port);
    Address(unsigned char fst, unsigned char snd, unsigned char thd, unsigned char fth, unsigned short port);

    unsigned GetAddress() const;
    unsigned short GetPort() const;

    unsigned char GetFst() const;
    unsigned char GetSnd() const;
    unsigned char GetThd() const;
    unsigned char GetFth() const;

    const bool operator == (const Address& rhs);
    const bool operator != (const Address& rhs);

protected:
private:
    unsigned m_address;
    unsigned short m_port;
};

} // namespace pony

#endif // PONY_ADDRESS_HPP

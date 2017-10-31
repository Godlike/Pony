/*
 * Copyright (C) 2017 by Godlike
 * This code is licensed under the MIT license (MIT)
 * (http://opensource.org/licenses/MIT)
 */
/* Original story "Networking for Game Programmers" by Glenn Fiedler
 */

#ifndef ___PONY__ADDRESS_HPP___
#define ___PONY__ADDRESS_HPP___

namespace pony
{
/**
 * @brief Address
 *
 * IP Address/Port pair.
 */
class Address
{
public:
    Address();
    Address(const unsigned int address);
    Address(const unsigned int address, const unsigned short port);
    Address(const unsigned char fst, const unsigned char snd, const unsigned char thd, const unsigned char fth, const unsigned short port);

    unsigned int GetAddress() const;
    unsigned short GetPort() const;

    unsigned char GetFst() const;
    unsigned char GetSnd() const;
    unsigned char GetThd() const;
    unsigned char GetFth() const;

    const bool operator == (const Address & rhs);
    const bool operator != (const Address & rhs);

protected:
private:
    unsigned int m_address;
    unsigned short m_port;
};

} // namespace Pony

#endif // ___PONY__ADDRESS_HPP___

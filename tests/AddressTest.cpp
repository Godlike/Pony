
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <pony/Address.hpp>

using namespace pony;

TEST_CASE("Address defaults test", "[]")
{
    Address address;

    REQUIRE(0xef000001 == address.GetAddress());
    REQUIRE(0xffff == address.GetPort());
}

TEST_CASE("Address tests", "[]")
{
    Address address(0xef, 0x0, 0x0, 0x1, 0xffff);

    REQUIRE(0xef000001 == address.GetAddress());
    REQUIRE(0xffff == address.GetPort());
}

TEST_CASE("Address tests 2", "[]")
{
    Address address(0xef000001, 0xffff);

    REQUIRE(0xef000001 == address.GetAddress());
    REQUIRE(0xffff == address.GetPort());
}

TEST_CASE("Equal test", "[]")
{
    Address addrA(0xef000001, 0xffff);
    Address addrB(0xef000001, 0xffff);

    REQUIRE(addrA.GetAddress() == addrB.GetAddress());
    REQUIRE(addrA.GetPort() == addrB.GetPort());
}

TEST_CASE("Not equal test", "[]")
{
    Address addrA(0xef000001, 0xffff);
    Address addrB(0xef000002, 0xfffe);

    REQUIRE(addrA.GetAddress() != addrB.GetAddress());
    REQUIRE(addrA.GetPort() != addrB.GetPort());
}


#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <pony/Address.hpp>

using namespace pony;

TEST_CASE("Address defaults test", "[]")
{
    Address address;

    REQUIRE(0 == address.GetAddress());
    REQUIRE(0 == address.GetPort());
}

TEST_CASE("Address tests", "[]")
{
    Address address(0x7f000001, 0x8235);

    REQUIRE(0x7f000001 == address.GetAddress());
    REQUIRE(0x8235 == address.GetPort());
}

TEST_CASE("Address tests 2", "[]")
{
    Address address(127,0,0,1, 33333);

    REQUIRE(0x7f000001 == address.GetAddress());
    REQUIRE(33333 == address.GetPort());
}

TEST_CASE("Equal test", "[]")
{
    Address addrA(127,0,0,1, 33333);
    Address addrB(127,0,0,1, 33333);

    REQUIRE(addrA.GetAddress() == addrB.GetAddress());
    REQUIRE(addrA.GetPort() == addrB.GetPort());
}

TEST_CASE("Not equal test", "[]")
{
    Address addrA(127,0,0,1, 33333);
    Address addrB(127,0,0,2, 33334);

    REQUIRE(addrA.GetAddress() != addrB.GetAddress());
    REQUIRE(addrA.GetPort() != addrB.GetPort());
}

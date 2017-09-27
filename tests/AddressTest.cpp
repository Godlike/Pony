
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "pony/Address.hpp"

using namespace pony;

TEST_CASE("Address dummy test", "[]")
{
    Address address;

    REQUIRE(0xef000001 == address.GetAddress());
    REQUIRE(0xffff == address.GetPort());
}

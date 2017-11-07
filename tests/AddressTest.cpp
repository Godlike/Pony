
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <pony/Address.hpp>

using namespace pony;

TEST_CASE("Address Class", "[Address]")
{
    Address A;
    REQUIRE(0 == A.GetAddress());
    REQUIRE(0 == A.GetPort());

    Address B(30000);
    REQUIRE(0 == B.GetAddress());
    REQUIRE(30000 == B.GetPort());

    Address C(30000, ((127 < 24) | 0x1));
    REQUIRE(((127 < 24)| 0x1) == C.GetAddress());
    REQUIRE(30000 == C.GetPort());
}

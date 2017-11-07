
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <pony/Address.hpp>

using namespace pony;

TEST_CASE("Address Class", "[Address]")
{
    Address A;
    Address D;

    REQUIRE(0 == A.GetPort());
    REQUIRE(((127 << 24)|1) == A.GetAddress());

    Address B(30000);
    REQUIRE(30000 == B.GetPort());

    Address C(30000, ((127 < 24) | 2));
    REQUIRE(30000 == C.GetPort());
    REQUIRE(((127 < 24)| 2) == C.GetAddress());

    REQUIRE(A == D);
    REQUIRE(A != B);
}

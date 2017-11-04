
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <pony/Address.hpp>

using namespace pony;

TEST_CASE("Address Class", "[Address]")
{
    SECTION( "Address initialization by default" )
    {
	Address address;

	REQUIRE(0 == address.GetAddress());
	REQUIRE(0 == address.GetPort());
    }

    SECTION( "Address initialization by Address, Port pair in numeric notation" )
    {
	Address address(0x7f000001, 0x8235);

	REQUIRE(0x7f000001 == address.GetAddress());
	REQUIRE(0x8235 == address.GetPort());
    }

    SECTION( "Address initialization by Address, Port pair in dot decimal notation" )
    {
	Address address(127,0,0,1, 30000);

	REQUIRE(127 == address.GetAddressPart(1));
	REQUIRE(  0 == address.GetAddressPart(2));
	REQUIRE(  0 == address.GetAddressPart(3));
	REQUIRE(  1 == address.GetAddressPart(4));
    }

    SECTION( "Address equality/not equality ")
    {
	Address A(127,0,0,1, 30000);
	Address B(127,0,0,1, 30000);
	Address C(127,0,0,2, 30001);

	REQUIRE(A.GetAddress() == B.GetAddress());
	REQUIRE(A.GetPort() == B.GetPort());

	REQUIRE(A.GetAddress() != C.GetAddress());
	REQUIRE(A.GetPort() != C.GetPort());
    }
}


#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <pony.hpp>

using namespace std;
using namespace pony;

TEST_CASE("Pony - Godlike network infrastructure", "General tests") {

    SECTION( "Address & Port by default" ) {
        Address Addr;
        REQUIRE( 0 == Addr.GetAddress() );
        REQUIRE( 0 == Addr.GetPort() );
    }
    SECTION( "Address & port inits" ) {
        Address Addr(0x7f000001, 3000);
        REQUIRE( 0x7f000001 == Addr.GetAddress() );
        REQUIRE( 3000 == Addr.GetPort() );
    }
    SECTION( "Address & port inits" ) {
        Address Addr(0x7f, 0x00, 0x00, 0x01, 3000);
        REQUIRE( 0x7f000001 == Addr.GetAddress() );
        REQUIRE( 3000 == Addr.GetPort() );
    }
    SECTION( "Socket by default" ) {
        Socket Sock;
        REQUIRE(false == Sock.IsOpen());
    }
}

SCENARIO("Godlike network infrastructure tests", "Pony") {

    GIVEN( "Pony class" ) {

        WHEN( "Address & Socket" ) {
            Address Addr;
            Socket Sock;
            THEN( "By default" ) {
                REQUIRE( 0 == Addr.GetAddress());
                REQUIRE( 0 == Addr.GetPort());
                REQUIRE(false == Sock.IsOpen());
            }
        }

        WHEN( "Address only" ) {
            Address Addr;
            THEN( "By default" ) {
                REQUIRE( 0 == Addr.GetAddress());
                REQUIRE( 0 == Addr.GetPort());
            }
        }

        WHEN( "Socket only" ) {
            Socket Sock;
            THEN( "By default" ) {
                REQUIRE(false == Sock.IsOpen());
            }
        }

    }

}

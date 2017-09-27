
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "pony/Address.hpp"
#include "pony/Socket.hpp"

using namespace pony;

TEST_CASE("Socket dummy test", "[]")
{
    Socket socket;

    REQUIRE(false == socket.IsOpen());
}


#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <pony/Socket.hpp>

#include <ostream>

using namespace pony;

TEST_CASE("Invalid initialization", "[Socket]")
{
    SocketsInit();

    Socket socket;

    REQUIRE(false == socket.IsOpen());

    SocketsKill();
}

const uint16_t port = 33333;
const uint32_t localhost = (0x1 | 127 << 24);
const int8_t data[] = "Hello world!";

TEST_CASE("Valid initialization", "[Socket]")
{
    SocketsInit();

    Socket socket;

    REQUIRE(socket.Open(port));
    REQUIRE(true == socket.IsOpen());

    socket.Close();

    SocketsKill();
}

TEST_CASE("Hello World!", "[Socket]")
{
    SocketsInit();

    Socket socket;

    REQUIRE(true == socket.Open(port));

    REQUIRE(true == socket.IsOpen());

    uint32_t nrTest = 10;
    do {
	REQUIRE(socket.Send(Address(localhost, port), data,sizeof data) > 0);

	Address sender;
	int8_t buff[256];

	int32_t received = socket.Received(sender, buff,sizeof buff);
	if (received)
	{
	    REQUIRE(sizeof data == received);
	    std::cout << buff << std::endl;
	    REQUIRE(localhost == sender.GetAddress());
	    REQUIRE(port == sender.GetPort());
	}
    } while (--nrTest);

    socket.Close();

    SocketsKill();
}

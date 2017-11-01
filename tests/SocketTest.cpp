
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

const unsigned short port = 33333;

TEST_CASE("Valid initialization", "[Socket]")
{
    SocketsInit();

    Socket socket;

    REQUIRE(socket.Open(port));
    REQUIRE(true == socket.IsOpen());

    socket.Close();

    SocketsKill();
}

const char data[] = "Hello world!";
const unsigned int localhost = (0x1 | 127 << 24);

unsigned nrTest = 10;

TEST_CASE("Hello World!", "[Socket]")
{
    SocketsInit();

    Socket socket;

    REQUIRE(true == socket.Open(port));

    REQUIRE(true == socket.IsOpen());

    do {
	REQUIRE(socket.Send(Address(localhost,port), data,sizeof data) > 0);

	Address sender;
	char buff[256];

	signed received = socket.Recv(sender, buff,sizeof buff);
	if (received) {
	    REQUIRE(sizeof data == received);
	    std::cout << buff << std::endl;
	    REQUIRE(localhost == sender.GetAddress());
	    REQUIRE(port == sender.GetPort());
	}
    } while (--nrTest);

    socket.Close();

    SocketsKill();
}

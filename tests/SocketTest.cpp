
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <pony/Socket.hpp>

#include <ostream>

using namespace pony;

TEST_CASE("Invalid initialization", "[Socket]")
{
    socketsInit();

    Socket socket;

    REQUIRE(false == socket.IsOpen());

    socketsKill();
}

const unsigned short port = 33333;

TEST_CASE("Valid initialization", "[Socket]")
{
    socketsInit();

    Socket socket;

    REQUIRE(socket.Open(port));
    REQUIRE(true == socket.IsOpen());

    socket.Close();

    socketsKill();
}

const char data[] = "Hello world!";
const unsigned int localhost = (0x1 | 127 << 24);

unsigned nrTest = 1;

TEST_CASE("Hello World!", "[Socket]")
{
    socketsInit();

    Socket socket;

    REQUIRE(true == socket.Open(port));

    REQUIRE(true == socket.IsOpen());

    do {
	REQUIRE(socket.Send(Address(localhost,port), data,sizeof data) > 0);

	Address sender;
	char buff[256];

	REQUIRE(socket.Recv(sender, buff,sizeof buff) == sizeof data);
	REQUIRE(localhost == sender.GetAddress());
	REQUIRE(port == sender.GetPort());

	std::cout << buff << std::endl;

    } while (--nrTest);

    socket.Close();

    socketsKill();
}


#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <pony/Socket.hpp>

using namespace pony;

TEST_CASE("Socket default test", "[]")
{
    Socket socket;

    REQUIRE(socketsInit());
    REQUIRE(false == socket.IsOpen());
    socketsKill();
}

TEST_CASE("Socket test", "[]")
{
    Socket socket;

    REQUIRE(socketsInit());

    REQUIRE(socket.Open(33333));
    REQUIRE(true == socket.IsOpen());
    socket.Close();

    socketsKill();
}

TEST_CASE("Socket testing", "[]")
{
    Socket socket;

    REQUIRE(socketsInit());

    REQUIRE(socket.Open(33333));
    REQUIRE(true == socket.IsOpen());
    while(true)
    {
	const char data[] = "hello world!";

	socket.Send(Address(127,0,0,1,33333), data,sizeof data);
	while(true)
	{
	    Address sender;
	    unsigned char buff[256];
	    int bytes = socket.Recv(sender, buff,sizeof buff);
	    if ( ! bytes)
		break;
	    printf("received packet from %x:%d (%d bytes)\n",
		    sender.GetAddress(), sender.GetPort(), bytes);
	}

	//wait_seconds(0.25f);
    }
    socket.Close();

    socketsKill();
}


#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <pony/Socket.hpp>
#include <ostream>

using namespace pony;
using namespace std;

TEST_CASE("Socket Class", "[Socket]")
{
    SECTION( "Sockets initialization" )
    {
        InitSockets();
    }

    SECTION( "Hello world!" )
    {
        Socket socket;
        const uint16_t port = 30000;

        REQUIRE(false == socket.IsOpen());
        REQUIRE(socket.Open(port));
        REQUIRE(true == socket.IsOpen());

        uint32_t nrTest = 10;
        do {
            const uint32_t localhost = (0x1 | (127 << 24));
            const char data[] = "Hello world!";

            REQUIRE(0 < socket.Send(Address(port, localhost), data,sizeof data));

            Address sender;
            char buff[256];
            int32_t received = socket.Receive(sender, buff,sizeof buff);
            if (received)
            {
                REQUIRE(sizeof data == received);
                cout << buff << endl;
                //cout << "address = " << sender.GetAddress();
                //cout << "port = " << sender.GetPort();
                REQUIRE(localhost == sender.GetAddress());
                REQUIRE(port == sender.GetPort());
            }
        } while (--nrTest);

        socket.Close();
        REQUIRE(false == socket.IsOpen());
    }

    SECTION( "Sockets deinitialization" )
    {
        DeinitSockets();
    }
}

/* Original story "Networking for Game Programmers" by Glenn Fiedler
 */

#ifndef PONY_HPP
#define PONY_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

namespace pony {

class Address
{
    unsigned int address;
    unsigned short port;

public:
    Address(unsigned int _address = 0, unsigned short _port = 0)
        : address(_address), port(_port) {}

    Address(unsigned char fst, unsigned char snd, unsigned char thd
            ,unsigned char fth, unsigned short prt) : port(prt) {
        address = (fst << 24) | (snd << 16) | (thd << 8) | fth;
    }

    unsigned int GetAddress() const { return address; }

    unsigned short GetPort() const { return port; }

    bool operator == (const Address & rhs) const {
        return address == rhs.address && port == rhs.port;
    }

    bool operator != (const Address & rhs) const {
        return !(*this == rhs);
    }
};

class Socket
{
    int socket;

public:
    Socket() : socket(0) {}

    bool IsOpen() const { return socket > 0; }
    void Close() {
        if ( ! socket)
            return;
        close(socket);
        socket = 0;
    }

    bool Open(unsigned short port) {
        if ((socket != 0) || (port <= 0))
            return false;

        socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (socket <= 0) {
            socket = 0;
            return false;
        }

        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons((unsigned short) port);

        if (bind(socket, (const sockaddr*) &address, sizeof(sockaddr_in)) < 0){
            Close();
            return false;
        }

        // set non-blocking io
        int nonBlocking = 1;
        if (fcntl(socket, F_SETFL, O_NONBLOCK, nonBlocking) == -1) {
            Close();
            return false;
        }

        return true;
    }

    int Send(const Address & dst, const void * data, int size) {
        if ((socket == 0) || ( ! data) || (size <=0))
            return -1;

        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = htonl(dst.GetAddress());
        address.sin_port        = htons((unsigned short) dst.GetPort());

        int sended_bytes = sendto(socket, (const char*)data, size, 0,
                                  (sockaddr*)&address, sizeof(sockaddr_in));
        if (size - sended_bytes)
            return 0;

        return sended_bytes;
    }

    int Receive(Address & sender, void * data, int size) {
        if ((socket == 0) || ( ! data) || (size <=0))
            return -1;

        sockaddr_in from;
        socklen_t fromLength = sizeof(from);

        int received_bytes = recvfrom(socket, (char*)data, size, 0,
                                      (sockaddr*)&from, &fromLength);

        if (received_bytes <= 0)
            return 0;

        unsigned int address = ntohl(from.sin_addr.s_addr);
        unsigned int port = ntohs(from.sin_port);
        sender = Address(address, port);

        return received_bytes;
    }
};

}

#endif // PONY_HPP

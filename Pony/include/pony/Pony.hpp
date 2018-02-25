/*
 * Copyright (C) 2017 by Godlike
 * This code is licensed under the MIT license (MIT)
 * (http://opensource.org/licenses/MIT)
 */

#ifndef PONY_HPP
#define PONY_HPP

// For uint16_t, uint32_t
#include <cstdint>

#ifdef WIN32
#include <winsock2.h>   // For socket(), connect(), send(), and recv()
#include <ws2tcpip.h>   // for ipv6
typedef int socklen_t;
// Type used for raw data on this platform
typedef char raw_type;
#else
#include <sys/types.h>  // For data types
#include <sys/socket.h> // For socket(), connect(), send(), and recv()
#include <netdb.h>      // For gethostbyname(), in_port_t
#include <arpa/inet.h>  // For inet_addr()
#include <unistd.h>     // For close()
#include <netinet/in.h> // For sockaddr_in
// Type used for raw data on this platform
typedef void raw_type;
#endif

/** An address and a port for a socket aggregate. */
class Address
{
public:
    /** Type of protocol being requested. */
    enum PROTO { UNKNOW_SOCKET, TCP_SOCKET, UDP_SOCKET };

    /** 
     * Make an Address
     * If used as a default constructur, the Address was created in
     * an uninitialized state.
     * Otherwise make an Address for the given host and service.
     */
    Address(const char *host = NULL, const char *service = NULL,
            PROTO proto = UNKNOW_SOCKET);

    /** Make an Address for the given host and port number. */
    Address(const char *host, uint16_t port, PROTO proto);

    /** Return a string representation of the address. */
    const char * getAddress() const;

    /** Return the service in a string representation. */
    const char * getService() const;
    
    /** Return a numeric representation of the service - port. */
    uint16_t getPort() const;
    
    bool operator== (const Address& rhs) const;
    bool operator!= (const Address& rhs) const;

private:
    /** Raw address portion of this object. */
    sockaddr_storage m_addr;

    /** Number of bytes used in the addr field. */
    socklen_t m_slen;
};

/** The BSD socket wrapper. */
class Socket {
public:
    virtual ~Socket();
    
    /** If WinSock, load the WinSock DLLs; otherwise do nothing. */
    static bool startUp();
    /** If WinSock, unload the WinSock DLLs; otherwise do nothing. */
    static void cleanUp();

    /** Create the socket. */
    void createSocket(const Address &address, int type, int protocol);
    
    /** Bind the socket to given Address. */
    void bind(const Address &localAddress);
    
    /** Close this socket. */
    void close();
    
private:
    /** Address descriptor. */
    Address addrDesc;
    /** Socket descriptor. */
    int sockDesc;
    
protected:
    /** Construct this via a derived class only. */
    Socket();

};

/** UDP Peer or EndPoint class */
class UDPPeer : public Socket
{
public:
    /** Construct a UDPPeer (Client - Server) */
    UDPPeer();
    ˜UDPPeer();

    /**
     * Send the given buffer as a UDP datagram to the specified address/port.
     * @param buffer buffer to be written.
     * @param len number of bytes to write.
     * @param foreignAddress address to send to.
     * @return number of bytes received and -1 for error.
     */
    int sendTo(const void *buf, int len, const Address &foreignAddress);

    /**
     * Receie the bufferLen bytes of UDP datagram from this socket.
     * The given buffer is where the data will be placed.
     * @param buffer buffer to receive data.
     * @param len maximum number of bytes to receive.
     * @param sourceAddress address of datagram source.
     * @return number of bytes received and -1 for error.
     */
    int recvFrom(void *buf, int len, Address &sourceAddress);
};

#endif

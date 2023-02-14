#include <stdio.h>

class SocketTCP
{
private:
    int socketId; 
public:
    SocketTCP();
    ~SocketTCP();
};

class ClientTCP : public SocketTCP
{
    private:
    public:
}

class ServerTCP : public SocketTCP
{
    private:
    public:
}

class Connessione
{
    private:
    public:
}

class ClientConnessione : public Connessione
{
    private:
    public:
}

class ServerConnessione : public Connessione
{
    private:
    public:
}

class Address
{
    private:
    public:
}




//SocketTCP
SocketTCP::SocketTCP()
{
    socketId = socket(AF_INET, SOCK_DGRAM, 0);
}

SocketTCP::~SocketTCP()
{
    close(socketId);
}

//ClientTCP
ClientTCP::

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Address.hpp"

#define IP_DHCP "0.0.0.0"

class ClientTCP
{
private:
    int socketId;
public:
    ClientTCP();
    ~ClientTCP();
    bool connetti(char *ip, int port);
    bool connetti(Address server);
    bool invia(char* msg);
    bool invia(char* msg, void* buf);
    char* ricevi();
    char* ricevi(int &len);
};

ClientTCP::ClientTCP()
{
    socketId = socket(AF_INET, SOCK_STREAM, 0);
    if(socketId < 0) errore("socket()",-1);
}

ClientTCP::~ClientTCP()
{
}

bool ClientTCP::connetti(char* ip, int port)
{
    Address.Address(ip, port);
    connetti(Address.inet_address);
}

bool ClientTCP::connetti(Address server)
{

}

bool ClientTCP::invia(char* msg)
{

}

bool ClientTCP::invia(char* msg, void* buf)
{

}

char* ClientTCP::ricevi()
{

}

bool ClientTCP::ricevi(int &len)
{

}

int errore(char* typeErr, int levErr){
    printf("%s", typeErr);
    return levErr;
}

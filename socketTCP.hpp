#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define IP_DHCP "0.0.0.0"
#define MAX_CONN 50
#define MAX_DIM 4096

class SocketTCP
{
private:
    int socketId;
    struct sockaddr_in serverAddr; 
public:
    SocketTCP(int port);
    ~SocketTCP();
    struct sockaddr_in getServerAddr(); 
    int getSocketId();
};

class ServerTCP : public SocketTCP
{
    private:
        int connId;
    public:
        void createServer();
        void accetta();
        char* startServer(char* msg);
};

class ClientTCP : public SocketTCP
{
    private:
    public:
};

class Connessione
{
    public:
        bool invia(int id, char* msg);
        char* ricevi(int id);
};

class ClientConnessione : public Connessione
{
    public:
        int shutdown();

};

class ServerConnessione : public Connessione
{
    public:
        bool invia(int connId, char* msg);
        char* ricevi();
};





//funzione errore generica
void errore(char* typeErr, int livErr)
{
    printf("ERROR on: %s", typeErr);
    exit(livErr);
}

//SocketTCP
SocketTCP::SocketTCP(int port)
{
    socketId = socket(AF_INET, SOCK_DGRAM, 0);
    if(socketId <= 0) errore("socket()", -1);

    serverAddr.sin_family = AF_INET;
    inet_aton(IP_DHCP, &serverAddr.sin_addr); 
    serverAddr.sin_port = htons(port);
    for(int i=0; i<8; i++) serverAddr.sin_zero[i]=0;
}

SocketTCP::~SocketTCP()
{
    close(socketId);
}

struct sockaddr_in SocketTCP::getServerAddr()
{
    return serverAddr;
}

int SocketTCP::getSocketId()
{
    return socketId;
}



//ServerTCP
void ServerTCP::createServer()
{
    struct sockaddr_in server = SocketTCP::getServerAddr();
    int socketId = SocketTCP::getSocketId();
    int rc = bind(socketId, (struct sockaddr*) &server, (socklen_t)sizeof(server));
    if(rc < 0) errore("bind()", -2);

    listen(socketId, MAX_CONN);
    if(rc < 0) errore("listen()", -3);
}

void ServerTCP::accetta()
{
    struct sockaddr_in clientAddr;
    int lenAddr = sizeof(struct sockaddr);
    connId = accept(SocketTCP::getSocketId(), (struct sockaddr*)&clientAddr, (socklen_t)&lenAddr);
    if(connId <= 0) errore("accept()", -4);
}

char* ServerTCP::startServer(char* msg)
{
    ServerConnessione sc;
    bool stateInvia = sc.invia(connId, msg);
    if(stateInvia==false) errore("invia()", -7);
    return sc.ricevi();
}

//ClientTCP

//Connessione
bool Connessione::invia(int id, char* msg)
{
    int lenMsg = strlen(msg);
    int rc = send(id, msg, lenMsg, 0);
    if(rc != lenMsg)
    {
        errore("send()", -5);
    }else{
        return true;
    }
}

char* Connessione::ricevi(int id)
{
    char buffer[MAX_DIM+1];
    int ret = recv(id, buffer, MAX_DIM, 0);
    if(ret <= 0){
        errore("recv()", -6);
    }else{
        buffer[ret] = '\0';
        return strdup(buffer);
    }
}

bool ServerConnessione::invia(int connId, char* msg)
{  
    Connessione c;
    return c.invia(connId, msg);
}

int ClientConnessione::shutdown()
{
    int rc = shutdown(, SHUT_RDWR);
}
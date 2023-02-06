#ifndef __ADDRESS_HPP__
#define __ADDRESS_HPP__

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>

#define IP_DHCP "0.0.0.0"
#define IP_LO "127.0.0.1"
#define MAX_STR 30

class Address {
    private:
        struct sockaddr_in inet_address;
        static pthread_mutex_t mutex;
    public:
        Address();
        Address(Address const &);
        Address(char*, int);
        ~Address();

        void    set_inet_address(struct sockaddr_in);
        void    set_ip(char*);
        void    set_port(int);

        struct sockaddr_in  get_inet_address();
        char*               get_ip();
        int                 get_port();

        char*   toString();
};

pthread_mutex_t Address::mutex = PTHREAD_MUTEX_INITIALIZER;

Address::Address():Address(IP_DHCP, 0) { } //Richiama il metodo sottostante
Address::Address(char* ip,int port){
    inet_address.sin_family = AF_INET;
    set_ip(ip);
    set_port(port);
    for(int i=0; i<8; i++) inet_address.sin_zero[i] = 0;
}
Address::Address(Address const &a){ //costruttore per copia
    this->inet_address = a.inet_address; //copia il vecchio address in quello della nuova classe
}

Address::~Address() { } //Distruttore esplicito



void Address::set_inet_address(struct sockaddr_in a)    { this->inet_address = a; }

void Address::set_ip(char* ip)   { inet_aton(ip, &inet_address.sin_addr); }

void Address::set_port(int port)    { inet_address.sin_port = htons(port); }

struct sockaddr_in Address::get_inet_address()  { return inet_address; }

char* Address::get_ip(){
    pthread_mutex_lock(&mutex);
    return strdup(inet_ntoa(inet_address.sin_addr));
    pthread_mutex_unlock(&mutex);
}

int Address::get_port() { return ntohs(inet_address.sin_port); }


char* Address::toString(){
    char buffer[MAX_STR];
    int port = get_port();
    char* ip = get_ip();
    sprintf(buffer, "[%s:%d]", ip, port);
    free(ip); //malloc generata dal get_ip()
    return strdup(buffer); //senza strdup buffer verrebbe eliminato alla fine della funzione
}

#endif // __ADDRESS_HPP__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int errore(char* typeErr, int levErr);

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("USAGE:%s ip port\n", argv[0]);
        return -1;
    }

    char* ip = argv[1];
    int port = atoi(argv[2]);
    char* msg = argv[3];

    //istaziamento statico => non serve il disposer perché lo farà da solo
    clientTCP client;
    if(client.connetti(ip, port)) errore("client.connetti(ip, port)", -2);

    if(client.invia(msg)) errore("client.invia(msg)", -3);

    char* response = client.rivevi();
    if(!response) errore("client.ricevi()", -4);
    printf("%s\n", msg);
    free(response);

    return 0;
}

int errore(char* typeErr, int levErr){
    printf("%s", typeErr);
    return levErr;
}
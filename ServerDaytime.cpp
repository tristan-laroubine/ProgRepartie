#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>



using namespace std;

void exitErreur(const char * msg) {
    perror(msg);
    exit( EXIT_FAILURE);

}

int main() {

    int sock_client = socket(AF_INET, SOCK_STREAM, 0);

    cout << "Client lancé"<< endl;

    int etat_connect;

    struct sockaddr_in sockaddr_serveur;
    inet_aton("139.124.187.23",&sockaddr_serveur.sin_addr);
    sockaddr_serveur.sin_family = AF_INET;
    sockaddr_serveur.sin_port = htons(80);

    socklen_t socklen = sizeof(sockaddr_serveur);


    if( (etat_connect = connect(sock_client,(struct sockaddr *) &sockaddr_serveur, socklen) )== -1)
        exitErreur("connect");

    string requete = "GET /tp1.html\n";
    if (write(sock_client, requete.c_str(), requete.size()) == -1)
        exitErreur("write");


    char msg [5];
    int taillemsg=1;
    while(taillemsg != 0){
    if ((taillemsg = read(sock_client, msg, sizeof (msg))) == -1)
        exitErreur("read");
    for(unsigned i = 0; i < taillemsg; ++i)
        cout << msg[i];
    }
    close(sock_client);

    cout << "fin " << endl;

    return 0;
}

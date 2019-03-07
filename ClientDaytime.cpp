#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <string>
#include <iostream>

using namespace std;

void exitErreur(const char * msg) {
    perror(msg);
    exit( EXIT_FAILURE);
}

int main(int argc, char** argv) {

    char ip[16];
    short port;

    if (argc < 3) {
        cout << "ip: " << flush;
        scanf("%s", ip);
        cout << "port: " << flush;
        scanf("%hu", &port);
    } else {
        strcpy(ip, argv[1]);
        port = atoi(argv[2]);
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    //sockaddr_serveur.sin_addr.s_addr = htonl(INADDR_ANY); //inet_addr("10.203.9.81");

    cout << inet_aton(ip, &addr.sin_addr) << endl;

    if (connect(sock, (struct sockaddr *) &addr,
            sizeof(sockaddr_in)) == -1)
        exitErreur("connect");

    char buf[1024];
    int len = 0;

    while (true) {
        std::string query;
        std::getline(std::cin, query);
        cout << "envoyé: " << query << endl;
        write(sock, query.c_str(), query.size());

        int ret = read(sock, buf+len, sizeof(buf)-len);
        if (ret == -1) {
            exitErreur("read");
        }

        if (ret == 0)
            break;

        len += ret;
    }


    buf[len] = 0;
    cout << "message (" << len << "): " <<  buf << endl;

    close(sock);
    return 0;
}

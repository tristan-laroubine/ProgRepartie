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
    inet_aton(ip, &addr.sin_addr);

    if (connect(sock, (struct sockaddr *) &addr,
            sizeof(sockaddr_in)) == -1)
        exitErreur("connect");

    while (true) {

        char httpquery[255];
        int inputlen = read(fileno(stdin), httpquery, sizeof(httpquery));
        httpquery[inputlen] = '\n';

        while (true) {
            write(sock, httpquery, inputlen);

            char buf[1024];
            int ret = read(sock, buf, sizeof(buf));

            if (ret == -1) {
                exitErreur("read");
            }

            if (ret == 0)
                break;

            buf[ret] = 0;
            cout << buf << endl;
        }
    }

    close(sock);
    return 0;
}

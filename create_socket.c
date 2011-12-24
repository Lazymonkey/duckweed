#include "duckweed.h"

void create_socket()
{
    int servdesc, clientdesc;
    socklen_t servsocklen, clisocklen;
    struct sockaddr_in servaddr, cliaddr;
    pid_t pid;

    if((servdesc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        exit(1);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port =htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(&servaddr.sin_zero, 0, 8);

    servsocklen = (socklen_t)sizeof( servaddr);
    clisocklen = (socklen_t)sizeof(cliaddr);

    if((bind(servdesc, (struct sockaddr *)&servaddr, servsocklen)) < 0) {
        perror("bind error");
        exit(1);
    }

    if(listen(servdesc, LISTEN_NUM) < 0) {
        perror("listen error");
        exit(1);
    }

    while(1) {

        if((clientdesc = accept(servdesc, (struct sockaddr *)&cliaddr,
                        &clisocklen)) < 0) {
            perror("accept error");
            exit(1);
        }

        if((pid = fork()) < 0) {
            perror("fork error");
            exit(1);
        }
        else if(pid == 0) {
            close(servdesc);
            exit(0);
        }
        else{
            handle_client(clientdesc);// cliaddr);
            close(clientdesc);
        }
    }
}

#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <fstream>
#include <string>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

#include <unistd.h>

#include "../Parser/parser.h"

const int  MAXLINE = 255;
const int SERVER_PORT = 1800;
typedef  sockaddr SA;


class Socket_reciver
{
public:
    Socket_reciver();
    void accept_clients();

private:
    int listenfd;
    int* connfd;
    sockaddr_in serv_addr;
    sockaddr_in cli_addr;
    pthread_t tid;

    static void* server_thread_routine(void *arg)
    {
        int _connfd;
        int n;
        char recv_line[MAXLINE];
        int pid;
        int recv_line_len;
        Redis client;

        _connfd = *(int*)arg;
        pthread_detach(pthread_self());

        if (_connfd < 0) {
            std::cerr <<  "ERROR on listen";
            exit(1);
        }
        while (1)
        {
            bzero(recv_line, MAXLINE);
            n = recv(_connfd, recv_line, MAXLINE, 0);
            printf("recv_line : %s\n", recv_line);
            if (!strcmp(recv_line, "EXIT")) { break; }
            if (n < 0) {
                std::cerr <<  "ERROR on read";
                break;
            }
            String recvLine(recv_line);
			recvLine = client.Parser(recvLine);
			recvLine += String("\n\r");
            send(_connfd, &recvLine[0], recvLine.size(), 0);
        }
        close(_connfd);
        free(arg);
        return 0;
    }
    int count_token(char *str, char token);
    char** get_arr_from_command(char *command);
};

#endif // SERVER_H
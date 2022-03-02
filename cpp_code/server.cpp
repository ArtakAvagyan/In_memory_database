#include <iostream>
#include <string>
#include <cstring>
#include "server.h"

using std::string;
using std::cout;

Socket_reciver::Socket_reciver()
{
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0)
    {
        std::cerr <<  "Error opening socket\n";
        std::exit(1);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("192.168.11.106");
    serv_addr.sin_port = htons(SERVER_PORT);
    if (bind(listenfd, (SA *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr <<  "ERROR on binding\n";
        exit(1);
    }
    cout << "server ip : " << inet_ntoa(serv_addr.sin_addr) << std::endl;
    if (listen(listenfd, 5) < 0)
    {
        std::cerr <<  "ERROR on listen\n";
        exit(1);
    }
}

void    Socket_reciver::accept_clients()
{
    while (1)
    {
        socklen_t client_len = sizeof(cli_addr);
        connfd = (int*)malloc(sizeof(int));
        *connfd = accept(listenfd, (SA *)&cli_addr, &client_len);
        pthread_create(&tid, NULL, server_thread_routine, (void*)connfd);
    }
}

int Socket_reciver::count_token(char *str, char token)
{
    int count;
    int i;

    count = 0;
    i = 0;
    while (str[i] && str[i + 1])
    {
        if (str[i] == token && str[i + 1] != token)
            ++count;
        ++i;
    }
    return (count);    
}

char**    Socket_reciver::get_arr_from_command(char *command)
{
    int     i;
    int     arr_len;
    char    **arr;

    i = 0;
    arr_len = count_token(command, ' ') + 2;
    arr = (char**)malloc(arr_len * sizeof(char*));
    arr[i] = strtok(command, " ");
    while (arr[i] != NULL) {
        arr[++i] = strtok(NULL, " ");
    }
    arr[i++] = NULL;
    return (arr);
}

// static void*   Socket_reciver::server_thread_routine(void *arg);

int main()
{
    Socket_reciver socket;
    socket.accept_clients();

    return (0);
}

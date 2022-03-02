#ifndef CLIENT_H
# define CLIENT_H

#include <sys/socket.h>
#include <arpa/inet.h>

#include <cstring>

#include <string>
#include <iostream>

using std::string;
using std::cout;

typedef  sockaddr SA;
const int MAXLINE = 255;
const int SERVER_PORT = 1800;

class Socket_sender
{
    public:
    Socket_sender();
    void    send_and_recv(const string&);
    ~Socket_sender();

    private:
    int                 sockfd;
    sockaddr_in         server_addr;
    string              server_ip;
    char                recv_line[255];
    string              send_line;
};


#endif

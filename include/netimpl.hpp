#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 50104

class Server
{
private:
    int sockfd, new_socket;
    sockaddr_in address;
    socklen_t addrlen;
    int opt = 1;
    ssize_t valread;
    char buffer[1024] = {0};
    char *hello = "Hello from server";

public:
    Server();
    Server(unsigned int socket_port);
    ~Server();

    void loop();
};

class Client
{
private:
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    

public:
    void loop();
};

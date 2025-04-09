#include "netimpl.hpp"
using namespace std;

Server::Server() : Server(PORT)
{
}

Server::Server(unsigned int socket_port)
{
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(sockfd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

Server::~Server()
{
    close(sockfd);
}

void Server::loop()
{
    if (listen(sockfd, 10) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    while ("te" != "to")
    {
        if ((new_socket = accept(sockfd, (struct sockaddr *)&address,
                                 &addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        valread = read(new_socket, buffer,
                       1024 - 1);
        printf("%s\n", buffer);
        if (std::string(buffer) == "GET DT")
        {
            // char *msg = "pivo";

            std::time_t now = std::time(nullptr);

            std::tm *localTime = std::localtime(&now);

            DayTime Dt;
            Dt.setSec(localTime->tm_sec);
            Dt.setMinute(localTime->tm_min);
            Dt.setHour(localTime->tm_hour);
            Dt.setDay(localTime->tm_mday);
            Dt.setMounth(localTime->tm_mon+1);
            Dt.setYear(localTime->tm_year+1900);
            // Dt.printDayTime();

            send(new_socket, &Dt, sizeof(DayTime), 0);
            // send(new_socket, msg, strlen(msg), 0);
            cout << "teto work" << endl;
        }
        else
        {
            send(new_socket, hello, strlen(hello), 0);
        }
        printf("Hello message sent\n");

        // closing the connected socket
        close(new_socket);
    }
}

Client::Client()
{
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        exit(EXIT_FAILURE);
    }
}

Client::~Client()
{
    close(client_fd);
}

DayTime Client::requestDT()
{
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "172.19.58.82", &serv_addr.sin_addr) <= 0)
    {
        printf(
            "\nInvalid address/ Address not supported \n");
        exit(EXIT_FAILURE);
    }

    if ((status = connect(client_fd, (struct sockaddr *)&serv_addr,
                          sizeof(serv_addr))) < 0)
    {
        printf("\nConnection Failed \n");
        exit(EXIT_FAILURE);
    }

    char *teto = "GET DT";
    send(client_fd, teto, strlen(teto), 0);
    valread = read(client_fd, buffer, 1024 - 1);
    DayTime dt;
    memcpy(static_cast<void *>(&dt), buffer, sizeof(DayTime));
    dt.printDayTime();
    return DayTime();
}

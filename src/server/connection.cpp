#include "connection.hpp"

int Connection::acceptConnection(int index)
{
    int optval = 1;
    int clientSocket = accept(serverSocketList[index], NULL, NULL);
    setsockopt(clientSocket, SOL_SOCKET, SO_NOSIGPIPE, &optval, sizeof(optval));
    if (clientSocket < 0)
        return -1;
    struct pollfd fd = {clientSocket, POLLIN, 0};
    fds.push_back(fd);
    Client client;
    client.setFdClient(fd);
    clients.insert(std::pair<int, Client>(fd.fd, client));
    return 0;
}

Connection::Connection(std::multimap<std::string, int> hostPort, std::vector<server> servers) : servers(servers)
{
    std::multimap<std::string, int>::iterator it;
    int i = 0;
    for (it = hostPort.begin(); it != hostPort.end(); it++)
    {
        serverSocketList.push_back(createsocket(it->second));
        std::cout << "port => " << it->second << std::endl;
        struct pollfd fd = {serverSocketList[i], POLLIN, 0};
        fds.push_back(fd);
        i++;
    }
    start();
}

int Connection::createsocket(int port)
{

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    if (serverSocket == -1)
    {
        std::cerr << "Failed to create server socket" << std::endl;
        exit(1);
    }
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "Failed to bind server socket to port " << port << std::endl;
        exit(1);
    }

    if (listen(serverSocket, 5) == -1)
    {
        std::cerr << "Failed to listen for incoming connections" << std::endl;
        exit(1);
    }
    return serverSocket;
}
void Connection::start()
{
    while (true)
    {
        // std::cout << "Waiting for incoming connections : "<< std::endl;

        if ((poll(&fds[0], fds.size(), -1)) < 0)
        {
            std::cerr << "Failed to poll" << std::endl;
            exit(1);
        }
        for (size_t i = 0; i < fds.size(); i++)
        {
            if (fds[i].revents & POLLHUP)
            {
                std::cout << "close connection\n";
                this->closeConnection(i);
            }
            else if (fds[i].revents & POLLIN)
            {
                if (i < serverSocketList.size() && fds[i].fd == serverSocketList[i])
                {
                    if (this->acceptConnection(i) == -1)
                    {
                        std::cerr << "Failed to accept connection" << std::endl;
                      break;
                    }
                }
                else if (clients.find(fds[i].fd) != clients.end())
                {
                    if (clients.find(fds[i].fd)->second.receiveRequest(this->servers))
                    {
                        fds[i].events = POLLOUT;
                        std::cout << clients.size() << std::endl;
                    }
                }
            }
            else if (fds[i].revents & POLLOUT)
            {
                if (clients.find(fds[i].fd)->second.sendResponse())
                    continue;
                if (clients.find(fds[i].fd)->second.status == BODY_DONE)
                {
                    std::cout << "close connection\n";
                    this->closeConnection(i);
                }
            }
            
        }
    }
}


void Connection::closeConnection(int index)
{
    close(fds[index].fd);
    this->clients.erase(fds[index].fd);
    fds.erase(fds.begin() + index);
}
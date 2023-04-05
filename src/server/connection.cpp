#include "define.hpp"

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
    for (it = hostPort.begin(); it != hostPort.end(); it++)
    {
        int serverSocket = createsocket(it->second, it->first);
        if(serverSocket == -1)
            continue;
        else
        {
            serverSocketList.push_back(serverSocket);
            std::cout << "port => " << it->second << std::endl;
            struct pollfd fd = {serverSocket, POLLIN, 0};
            fds.push_back(fd);
        }
    }
    if(serverSocketList.size() != 0)
        start();
}

int Connection::createsocket(int port, std::string host)
{

   int  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    if (serverSocket == -1)
    {
        std::cerr << "Failed to create server socket" << std::endl;
        return -1;
    }
    // int flags = fcntl(serverSocket, F_GETFL, 0);
    // fcntl(serverSocket, F_SETFL, flags | O_NONBLOCK);
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
        return -1;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(host.c_str());
    // serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
       std::cerr << "Failed to create server socket with host: " << host << " and port: " << port << std::endl;
        return -1;
    }

    if (listen(serverSocket, 10000) == -1)
    {
        std::cerr << "Failed to listen for incoming connections" << std::endl;
        return -1;
    }
    return serverSocket;
}
void Connection::start()
{
    while (true)
    {
        std::cout << "Waiting for incoming connections : "<< std::endl;

        if ((poll(&fds[0], fds.size(), -1)) < 0)
        {
            std::cerr << "Failed to poll" << std::endl;
            continue;
        }
        for (size_t i = 0; i < fds.size(); i++)
        {
            if (fds[i].revents & POLLHUP)
            {
                // std::cout << "close connection\n";
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
                else 
                {
                    if (clients.find(fds[i].fd)->second.receiveRequest(this->servers))
                        fds[i].events = POLLOUT;
                }
            }
            else if (fds[i].revents & POLLOUT)
            {
                if (clients.find(fds[i].fd)->second.sendResponse())
                    continue;
                if (clients.find(fds[i].fd)->second.status == BODY_DONE)
                {
                    // std::cout << "close connection\n";
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
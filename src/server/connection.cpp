#include "connection.hpp"

// void Connection::sendLargeFile(int clientSocket, const char *filePath)
// {
//     std::ifstream fileStream(filePath, std::ios::binary);
//     if (!fileStream.is_open())
//         return;
//     const int CHUNK_SIZE = 1024;
//     char buffer[CHUNK_SIZE];
//     int bytesRead = 0;
//     int i = 0;
//     struct pollfd pfd;
//     int timeout = -1;
//     pfd.fd = clientSocket;
//     pfd.events = POLLOUT;

//     // Wait for the socket to become ready for writing
//     int ret = poll(&pfd, 1, timeout);

//     if (ret == -1)
//     {
//         //std::cout << "Error" << std::endl;
//     }
//     else if (ret == 0)
//     {
//         //std::cout << "Timeout" << std::endl;
//     }
//     else
//     {
//         //std::cout << "----------------------------------------------\n";
//         while (fileStream.read(buffer, CHUNK_SIZE))
//         {
//             bytesRead = fileStream.gcount();
//             if(send(clientSocket, buffer, bytesRead, 0) == -1)
//                 return;
//             //std::cout << i << std::endl;
//             i++;
//         }
//         if (!fileStream.eof())
//             return;
//         bytesRead = fileStream.gcount();
//         if(bytesRead > CHUNK_SIZE)
//         {}
//         if (bytesRead > 0 && send(clientSocket, buffer, bytesRead, 0) == -1)
//             return;
//     }
// }

// bool Connection::receiveRequest(int clientSocket)
// {
//     //std::cout << clientSocket << " is readable" << std::endl;
//     bool close_conn = false;
//     char request[MAX_REQUEST_SIZE];
//     int numBytes = recv(clientSocket, request, MAX_REQUEST_SIZE, 0);
//     if (numBytes == -1)
//     {
//         std::cerr << "Failed to read request from client" << std::endl;
//         close(clientSocket);
//         exit(1);
//     }
//     if (numBytes == 0)
//     {
//         //std::cout << " Connection closed" << std::endl;
//         close_conn = true;
//     }
//     else
//     {
//         this->_request.parseRequest(request);
//         response res;
//         res.generateResponse(this->servers[0], this->_request);
//         this->sendResponse(clientSocket, res);
//     }
//     return close_conn;
// }

// void Connection::sendResponse(int clientSocket, response &res)
// {
//     std::string r;
//     // std::map<std::string, std::string> header = res.getHeaderMap();
//     r = res.getStatus() + "\r\n";
//     for (std::map<std::string, std::string>::iterator it = res.getHeaderMap().begin(); it != res.getHeaderMap().end(); it++)
//         r += it->first + ": " + it->second + "\r\n";
//     r += "\r\n";
//     if (send(clientSocket, r.c_str(), r.size(), 0) == -1)
//     {
//         close(clientSocket);
//         PrintExit("Failed to send response to client");
//     }
//     // r = readFileContent("./web_pages/miski1.mp4");
//     sendLargeFile(clientSocket, "./web_pages/miski1.mp4");
//     // if (send(clientSocket, r.c_str(), r.size(), 0) == -1)
//     // {
//     //     close(clientSocket);
//     //     PrintExit("Failed to send response to client");
//     // }
// }

Connection::Connection(std::multimap<std::string, int> hostPort, std::vector<server> servers) : servers(servers)
{
    std::multimap<std::string, int>::iterator it;
    int i = 0;
    for (it = hostPort.begin(); it != hostPort.end(); it++)
    {
        serverSocketList.push_back(createsocket(it->second));
        //std::cout << "port => " << it->second << std::endl;
        struct pollfd fd = {serverSocketList[i], POLLIN, 0};
        i++;
        fds.push_back(fd);
    }
    start();
}
void Connection::start()
{
    int optval = 1;
    while (true)
    {
        // std::cout << "Waiting for incoming connections : " << clients.size()<< std::endl;
       
        if ((poll(&fds[0], fds.size(), -1)) < 0)
        {
            std::cerr << "Failed to poll" << std::endl;
            exit(1);
        }
        for (size_t i = 0; i < fds.size(); i++)
        {

            if (fds[i].revents & POLLIN)
            {
                if (i < serverSocketList.size() && fds[i].fd == serverSocketList[i])
                {
                    int clientSocket = accept(serverSocketList[i], NULL, NULL);
                    setsockopt(clientSocket, SOL_SOCKET, SO_NOSIGPIPE, &optval, sizeof(optval));
                    if (clientSocket < 0)
                        break;
                    struct pollfd fd = {clientSocket, POLLIN, 0};
                    fds.push_back(fd);
                    Client client;
                    client.setFdClient(fd);
                    clients.insert(std::pair<int, Client>(fd.fd, client));
                    //std::cout << "new connection\n";
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
                if(clients.find(fds[i].fd)->second.sendResponse())
                    continue;
                // std::cout << "send response\n";
                if (clients.find(fds[i].fd)->second.status == BODY_DONE)
                {
                    std::cout << "close connection\n";
                    close(fds[i].fd);
                    clients.erase(fds[i].fd);
                    fds.erase(fds.begin() + i);
                }
            }
            if(fds[i].revents & POLLHUP)
            {
                std::cout << "close connection\n";
                close(fds[i].fd);
                clients.erase(fds[i].fd);
                fds.erase(fds.begin() + i);
            }
                     
        }
    }
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
    // bind socket to port
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
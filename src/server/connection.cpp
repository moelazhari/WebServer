#include "connection.hpp"

// void Connection::sendErrorPage(ParseRequest &request)
// {
//     // if (request.getURL().length() > 2048)
//     // {
//     // }
//     // else if ()//content-lenght > max body size
//     // {

//     // }
// }

void Connection::receiveRequest(int clientSocket)
{
    // std::cout << "clientSocket => " << clientSocket << std::endl;
    char request[MAX_REQUEST_SIZE]; // normalement  object request parser
    int numBytes = recv(clientSocket, request, MAX_REQUEST_SIZE, 0);
    if (numBytes == -1)
    {
        std::cerr << "Failed to read request from client" << std::endl;
        close(clientSocket);
        exit(1);
    }
    this->_request.parseRequest(request);
    //TODO get server
    response res;
    res.generateResponse(this->servers[0], this->_request);
    this->sendResponse(clientSocket, res);

    /*-----------------------------------------------------*/
    // fds.erase(fds.end() - 1);
    close(clientSocket);
}

void Connection::sendResponse(int clientSocket, response &res)
{
    std::string r;
    // std::map<std::string, std::string> header = res.getHeaderMap();
    
    r = res.getStatus() + "\r\n";
	for (std::map<std::string, std::string>::iterator it = res.getHeaderMap().begin(); it != res.getHeaderMap().end(); it++)
		r += it->first + ": " + it->second + "\r\n";
    r += "\r\n";
    if (send(clientSocket, r.c_str(), r.size(), 0) == -1)
    {
        close(clientSocket);
        PrintExit("Failed to send response to client");
    }
    r = res.getBody();
    if (send(clientSocket, r.c_str(), r.size(), 0) == -1)
    {
        close(clientSocket);
        PrintExit("Failed to send response to client");
    }

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
        i++;
        fds.push_back(fd);
    }
    start();
}
void Connection::start()
{
    while (true)
    {
        // std::cout << "Waiting for incoming connections port => " << std::endl;
        socklen_t addrLen = sizeof(struct sockaddr_in);
        if (poll(&fds[0], fds.size(), -1) < 0)
        {
            std::cerr << "Failed to poll" << std::endl;
            exit(1);
        }
        for (size_t i = 0; i < fds.size(); i++)
        {
            if (fds[i].revents & POLLIN)
            {
                if (fds[i].fd == serverSocketList[i])
                {

                    clientSocket = accept(serverSocketList[i], (struct sockaddr *)&clientAddr, &addrLen);
                    if (clientSocket == -1)
                    {
                        std::cerr << "Failed to accept incoming connection" << std::endl;
                        exit(1);
                    }
                    receiveRequest(clientSocket);
                }
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
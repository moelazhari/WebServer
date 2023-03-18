#include "connection.hpp"
#include "response.hpp"

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
    _request.parseRequest(request);
    //
    response _response;
    // chech_request(_request, _response);

    _response.generateResponse(this->servers[0], _request);
    std::string tmp = _response.joinResponse();
    const char *response = tmp.c_str(); //_response.sendResponse(clientSocket);
    // std::cout << "response => " << _response.joinResponse() << std::endl;
    // _request.affiche();
    //const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n    <meta charset=\"UTF-8\">\n    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n    <title>Document</title>\n</head>\n<body>\n    <h1>VAR TEST ROOT</h1>\n</body>\n</html>";
   std::cout << "response => " << response << std::endl;
    /*---------------response------------------------------------------------*/
    if (send(clientSocket, response, strlen(response), 0) == -1)
    {
        std::cerr << "Failed to send response to client" << std::endl;
        close(clientSocket);
        exit(1);
    }

    /*-----------------------------------------------------*/
    // fds.erase(fds.end() - 1);
    close(clientSocket);
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
        std::cout << "Waiting for incoming connections port => " << std::endl;
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
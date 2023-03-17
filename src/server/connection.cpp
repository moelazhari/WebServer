#include "connection.hpp"
#include "response.hpp"

void Connection::receiveRequest(int clientSocket)
{
    // std::cout << "clientSocket => " << clientSocket << std::endl;
    char request[MAX_REQUEST_SIZE]; // normalement  object request parser
    int numBytes = recv(clientSocket, request, MAX_REQUEST_SIZE, 0);
    if (numBytes == -1)
    {
        cerr << "Failed to read request from client" << endl;
        close(clientSocket);
        exit(1);
    }
    _request.parseRequest(request);

    // 
    response _response;
    _response.generateResponse(this->servers[0] ,_request);
    const char *response =  "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nHello World"; //_response.sendResponse(clientSocket);
    _request.affiche();

    /*---------------response------------------------------------------------*/
    if (send(clientSocket, response, strlen(response), 0) == -1)
    {
        cerr << "Failed to send response to client" << endl;
        close(clientSocket);
        exit(1);
    }

    /*-----------------------------------------------------*/
    // fds.erase(fds.end() - 1);
    close(clientSocket);
}

Connection::Connection(multimap<string, int> hostPort, std::vector<server> servers): servers(servers)
{
    multimap<string, int>::iterator it;
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
        cout << "Waiting for incoming connections port => " << endl;
        socklen_t addrLen = sizeof(struct sockaddr_in);
        if (poll(&fds[0], fds.size(), -1) < 0)
        {
            cerr << "Failed to poll" << endl;
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
                        cerr << "Failed to accept incoming connection" << endl;
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
        cerr << "Failed to create server socket" << endl;
        exit(1);
    }
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    memset(&serverAddr, 0, sizeof(serverAddr)); // clears the serverAddr struct variable to all zeros.
    serverAddr.sin_family = AF_INET;            // AF_INET is the address family for IPv4
    // htons() converts the unsigned short integerfrom host byte order to network byte order.
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        cerr << "Failed to bind server socket to port " << port << endl;
        exit(1);
    }
    if (listen(serverSocket, 5) == -1)
    {
        cerr << "Failed to listen for incoming connections" << endl;
        exit(1);
    }
    return serverSocket;
}
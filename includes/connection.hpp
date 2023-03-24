#pragma once

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include "server.hpp"
#include "ParseRequest.hpp"
#include "response.hpp"
#include "client.hpp"

#define MAX_SERVER 10
#define MAX_CONNECTIONS 10

class Connection
{
private:
        std::vector<server>     servers;
        std::vector<int>        serverSocketList;
        std::map<int, Client>  clients;


        int                     serverSocket;
        ParseRequest            _request;
        struct sockaddr_in      serverAddr;
        std::vector<struct pollfd> fds;
        struct pollfd           fd;
        long t;

public:
        Connection(std::multimap<std::string, int> hostPort, std::vector<server> servers);
        int createsocket(int port);
        // server getServer(std::vector servers);
        void handelRequest(std::vector<server> servers);
        void generate_respoonse(server &serv);
        void start();
        bool receiveRequest(int clientSocket);
        void sendErrorPage(ParseRequest &request);
        void sendResponse(int clientSocket, response &res);
        void sendLargeFile(int clientSocket, const char* filePath);
};

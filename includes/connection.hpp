#pragma once

#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include <map>
#include <vector>
#include "server.hpp"
using namespace std;
// #define port 8003
#define MAX_SERVER 10
#define MAX_CONNECTIONS 10
#define MAX_REQUEST_SIZE  1024
class Connection 
{
    private:
        int                 serverSocket;
        std::vector<server> servers;   
        vector<int>         serverSocketList;
        int                 clientSocket;
        ParseRequest        _request;
        struct sockaddr_in serverAddr;
        struct sockaddr_in clientAddr;
        vector<struct pollfd> fds;
    public:
        Connection(std::multimap<string, int> hostPort,  std::vector<server> servers);
        int createsocket(int port);
        // server getServer(std::vector servers);
        void handelRequest(vector<server> servers);
        void generate_respoonse(server& serv);
        void start();
        void receiveRequest(int clientSocket);
};

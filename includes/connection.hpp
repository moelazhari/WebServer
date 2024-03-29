#pragma once

#include "define.hpp"


class Connection
{
private:
        std::vector<server>             servers;
        std::vector<int>                serverSocketList;
        std::map<int, Client>           clients;
        ParseRequest                    _request;
        struct sockaddr_in              serverAddr;
        std::vector<struct pollfd>      fds;
        struct pollfd                   fd;
        long t;

public:
        Connection(std::multimap<std::string, int> hostPort, std::vector<server> servers);
        int     createsocket(int port, std::string host);
        // server getServer(std::vector servers);
        void    handelRequest(std::vector<server> servers);
        void    generate_respoonse(server &serv);
        void    start();
        bool    receiveRequest(int clientSocket);
        void    sendErrorPage(ParseRequest &request);
        void    sendResponse(int clientSocket, response &res);
        void    sendLargeFile(int clientSocket, const char* filePath);
        int     acceptConnection(int index);
        void    closeConnection(int index);
};

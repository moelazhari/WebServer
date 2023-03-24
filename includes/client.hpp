#pragma once

#include "ParseRequest.hpp"
#include "response.hpp"
#include <poll.h>
#include <unistd.h>
#include <sys/socket.h>
#include <server.hpp>
#define MAX_REQUEST_SIZE 1024
#define BUFFER_SIZE 1024
#define REDYTOWRITE 1
#define NOTREADYTOWRITE 0
#define HEADER_DONE 2
#define BODY_DONE 3

class Client
{
private:
    response        _response;
    server          _server;
    std::string     _requestString;
    struct pollfd   _fdClient;
    ParseRequest    _request;
    std::string     _body;
  
    

public:
    Client();
    ~Client();
    response &getResponse();
    pollfd &getFdClient();
    void setFdClient(struct pollfd fdClient);
    void setRequestString(std::string r);
    int receiveRequest(std::vector<server>     servers);
    int sendResponse();
    int sendPacket();
   std::string readbuffer();
    std::string generatHeader();
    int status;
};
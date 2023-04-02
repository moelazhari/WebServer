#pragma once

#include "ParseRequest.hpp"
#include "response.hpp"
#include <poll.h>
#include <unistd.h>
#include <sys/socket.h>
#include <server.hpp>
#include "define.hpp"

class Client
{
private:
    response        _response;
    server          _server;
    std::string     _requestString;
    struct pollfd   _fdClient;
    ParseRequest    _request;
    std::string     _req;
    std::string     _body;
    int             bodytype;
public:
    Client();
    ~Client();
    response    &getResponse();
    pollfd      &getFdClient();
    void        setFdClient(struct pollfd fdClient);
    int         receiveRequest(std::vector<server>     servers);
    int         sendResponse();
    int         sendPacket();
   std::string  readbuffer();
    std::string generatHeader();
    void        CheckReq(std::string r);
    void        checkHeader();
    void        recvBody(std::string r);
    void        parsechunked();
    int         status;
    void		defaultRes(int status);
};

size_t hexToDec(std::string hex);
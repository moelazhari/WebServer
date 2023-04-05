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
    struct pollfd   _fdClient;
    ParseRequest    _request;
    std::string     _req;
    std::string     _body;
    int             bodytype;

public:
    Client();
    response        &getResponse();
    pollfd          &getFdClient();
    void            setFdClient(struct pollfd fdClient);
    int             receiveRequest(std::vector<server> servers);
    int             sendResponse();
    std::string     readbuffer();
    std::string     generatHeader();
    void            CheckReq(std::string r);
    void            checkHeader();
    void            recvBody(std::string r);
    void            parsechunked();
    int             status;
    void            defaultRes(int status);
    void            setServer(std::vector<server> servers);
    ~Client();
};

int hexToDec(std::string hex);
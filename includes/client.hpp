#pragma once

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
    void            CheckReq(std::string r, std::vector<server> servers);
    void            checkHeader();
    void            recvBody(std::string r);
    void            parsechunked();
    int             status;
    void            defaultRes(int status);
    void            setServer(std::vector<server> servers);
    ~Client();
};
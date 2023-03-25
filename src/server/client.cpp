#include "client.hpp"

Client::Client() : status(NOTREADYTOWRITE)
{
}
Client::~Client()
{
}

response &Client::getResponse()
{
    return _response;
}

pollfd &Client::getFdClient()
{
    return _fdClient;
}

void Client::setFdClient(struct pollfd fdClient)
{
    _fdClient = fdClient;
}

void Client::setRequestString(std::string r)
{
    _requestString = r;
    // std::cout << "request => " << _requestString << std::endl;
}

int Client::receiveRequest(std::vector<server> servers)
{
    this->_server = servers[0];
    char request[MAX_REQUEST_SIZE];
    int numBytes = recv(_fdClient.fd, request, MAX_REQUEST_SIZE, 0);
    if (numBytes == -1)
    {
        std::cerr << "Failed to read request from client" << std::endl;
        close(_fdClient.fd);

        exit(1);
    }
    this->_request.parseRequest(request);
    this->_request.affiche();
    this->_response.generateResponse(this->_server, this->_request);
    return (1);
}
std::string Client::generatHeader()
{
    std::string r;
    r = this->_response.getStatus() + "\r\n";
    for (std::map<std::string, std::string>::iterator it = this->_response.getHeaderMap().begin(); it != this->_response.getHeaderMap().end(); it++)
        r += it->first + ": " + it->second + "\r\n";
    r += "\r\n";
    this->_body = this->_response.getBody();
    return r;
}
int Client::sendPacket()
{
    std::string r;
    if (this->status != HEADER_DONE)
    {
        r = generatHeader();
        this->status = HEADER_DONE;
    }
    else
    {
        if (this->_body.size() == 0)
        {
            this->status = BODY_DONE;
            return 0;
        }

        r = readbuffer();
    }
    if (send(this->getFdClient().fd, r.c_str(), r.size(), 0) == -1)
    {
        std::cout << "Failed to send response to client" << std::endl;
        return 1;
    }
    return 0;
}

int Client::sendResponse()
{
    return (this->sendPacket());
}

std::string Client::readbuffer()
{
    if (this->_body.size() > BUFFER_SIZE)
    {
        std::string buffer(this->_body.begin(), this->_body.begin() + BUFFER_SIZE);
        this->_body.erase(this->_body.begin(), this->_body.begin() + BUFFER_SIZE);
        return buffer;
    }
    this->status = BODY_DONE;

    return this->_body;
}
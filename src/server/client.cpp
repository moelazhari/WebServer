#include "client.hpp"

//for client
Client::Client() :  _req(""),  bytes(0), status(NOTREADY)
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
/*----------------------req-------------------------------*/
void Client::CheckReq(char rq[MAX_REQUEST_SIZE])
{
    std::string r(rq);
    if(r.find("\r\n\r\n") != std::string::npos)
    {
        this->status = REQ_HEADR_DONE;
        this->_req += r;
        this->bytes = this->_request.parseRequest(this->_req).size();
        this->bodytype = this->_request.CheckHeader(this->status);
        // this->_request.affiche();
    }
    else if(this->status == REQ_HEADR_DONE)
    {
        this->bytes += r.size();
        this->recvBody(r);
    }
    else
    {
        this->_req += r;
    }
    
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
    this->CheckReq(request);
    // this->_request.affiche();
    if(this->status == READYTO_RES)
    {
        this->_response.generateResponse(this->_server, this->_request);
        return (1);
    }
    else
        return (0);
}

void Client::recvBody(std::string r)
{
    if(this->bodytype == content_length)
    {
        if(toInt(this->_request.getHeaders()["Content-Length"]) <= this->bytes)
        {
            this->_request.setBody(r);
            this->status = READYTO_RES;
        }
        else
        {
            this->_request.setBody(r);
        }
    }
    else if(this->bodytype == transfer_encoding)
    {
        // if(this->_body.size() == 0)
        // {
        //     this->_body = r;
        // }
        // else
        // {
        //     this->_body = this->_body.substr(this->_body.find("\r\n"));
        // }
        
    }
    else if(this->bodytype == ERROR)
    {
        //errors   
    }
}

void Client::parsechunked(std::string r)
{
    std::string size = r.substr(0, r.find("\r\n"));
    std::string data = r.substr(r.find("\r\n") + 2);
    if(size.compare("0") == 0)
    {
        this->status = READYTO_RES;
    }
    else
    {
        if(data.size() != hexToDec(size))
        {
            this->status = ERROR;
        }
        else
        {
            this->_request.setBody(data);
        }
    }
}


/*-----------------for response-----------------------------*/
std::string Client::generatHeader()
{
    std::string r;
    r = this->_response.getStatus() + "\r\n";
    for (std::map<std::string, std::string>::iterator it = this->_response.getHeaderMap().begin(); it != this->_response.getHeaderMap().end(); it++)
        r += it->first + ": " + it->second + "\r\n";
    for (std::vector<std::string>::iterator it = this->_response.getCookies().begin(); it != this->_response.getCookies().end(); it++)
        r += "Set-Cookie: " + *it + "\r\n";

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
        std::cout << r << std::endl;
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

size_t hexToDec(std::string hex)
{
    int decimal;
    std::stringstream ss;
    ss << hex;
    ss >> std::hex >> decimal;
    return decimal;
}
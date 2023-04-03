#include "client.hpp"

// for client
Client::Client() : _req(""), status(NOTREADY)
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
void Client::defaultRes(int status)
{

    if (status == ERROR_400 || status == ERROR_501)
    {
        this->status = READYTO_RES;
        _response.setStatus(status);
        _response.fillResponse(this->_server, "");
        this->status = SEND_ERROR;
    }
}
/*----------------------req-------------------------------*/
void Client::CheckReq(std::string r)
{
    if (this->status != REQ_HEADR_DONE)
    {

        this->_req += r;
        if (this->_req.find("\r\n\r\n") != std::string::npos)
        {
            this->status = REQ_HEADR_DONE;
            this->_request.parseRequest(this->_req).size();
            this->bodytype = this->_request.CheckHeader(this->status);
            if (this->bodytype == transfer_encoding && this->_request.getBody().find("\r\n0\r\n") != std::string::npos)
            {
                this->parsechunked();
                this->status = READYTO_RES;
            }
            this->defaultRes(bodytype);
        }
    }
    else
    {
        this->recvBody(r);
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
    std::string r;
    for (int i = 0; i < numBytes; i++)
        r.push_back(request[i]);
    this->CheckReq(r);
    if (this->status == READYTO_RES)
    {
        this->_response.generateResponse(this->_server, this->_request);
        return (1);
    }
    else if (this->status == SEND_ERROR)
        return (1);
    else
        return (0);
}

void Client::recvBody(std::string r)
{
    if (this->bodytype == content_length)
    {
        std::cout << this->_request.getHeaders()["Content-Length"] <<  "==" << this->_request.getBody().size() + r.size() << std::endl;
        if (toInt(this->_request.getHeaders()["Content-Length"]) <= (int)(this->_request.getBody().size() + r.size()))
        {
            this->_request.setBody(r);
            this->status = READYTO_RES;
            // std::ofstream myfile("test.mp4", std::ios::binary);
            // myfile.write(this->_request.getBody().c_str(), this->_request.getBody().size());
            // std::cout << this->_request.getBody() << std::endl;
        }
        else 
            this->_request.setBody(r);
    }
    else if (this->bodytype == transfer_encoding)
    {
        this->_request.setBody(r);
        if (this->_request.getBody().find("\r\n\r\n") != std::string::npos)
        {
           this->parsechunked();
            this->status = READYTO_RES;
            // std::ofstream myfile("test.mp4", std::ios::binary);
            // myfile << this->_request.getBody();
        }
    }
    this->defaultRes(bodytype);
}

void Client::parsechunked()
{
    std::string input = this->_request.getBody();
    std::string output = "";
    while(true)
    {
        size_t pos = input.find("\r\n");
        if(input.size() <= 4 && input.substr(0, 2).compare("0\r\n\r\n") != 0)
        {
            bodytype = ERROR_400;
            break;
        }
        if (pos == std::string::npos)
            break;
        std::string size = input.substr(0, pos);
        if(hexToDec(size) == -1 || hexToDec(size) > (int)input.size())
        {
            bodytype = ERROR_400;
            break;
        }
        size_t chunk_size = hexToDec(size);
        if(chunk_size == 0)
            break;
        input = input.substr(pos + 2);
        output += input.substr(0, chunk_size);
        input = input.substr(chunk_size);
        if(input.substr(0, 2).compare("\r\n") != 0)
        {
            bodytype = ERROR_400;
            break;
        }
        input = input.substr(2);
    }
    this->_request.ClearBody();
    this->_request.setBody(output);
    
}
/*-----------------for response-----------------------------*/
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

int hexToDec(std::string hex)
{
    int decimal;
    std::stringstream ss;
    ss << hex;
    ss >> std::hex >> decimal;
    return decimal;
}
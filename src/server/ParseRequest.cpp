#include "ParseRequest.hpp"

ParseRequest::ParseRequest(): method(""), path(""), httpVersion(""), body("")
{}

std::string ParseRequest::parseRequest(const std::string &request)
{
    std::cout << "------------------request----------------------" << std::endl;
    int endOfLine = request.find("\r\n");
    std::string firstLine = request.substr(0, endOfLine);
    int endOfMethod = firstLine.find(" ");
    int endOfUrl = firstLine.find(" ", endOfMethod + 1);

    this->method = firstLine.substr(0, endOfMethod);
    this->path = firstLine.substr(endOfMethod + 1, endOfUrl - endOfMethod - 1);
    this->httpVersion = firstLine.substr(endOfUrl + 1, firstLine.size() - endOfUrl - 1);
    
    // std::cout << "path" << this->path << std::endl;
    size_t p = this->path.find("?");
    if (p != std::string::npos)
    {
        this->query = this->path.substr(p + 1);
        this->path = this->path.substr(0, p);
    }
    else 
        this->query = "";
    // std::cout << "url" << this->url << std::endl;

    size_t pos = endOfLine + 2;
    while (pos < request.length())
    {
        size_t end1 = request.find("\r\n\r\n", pos);
        if (end1 == std::string::npos)
            break;
        size_t end = request.find("\r\n", pos);
        if (end == std::string::npos)
            break;
        std::string line = request.substr(pos, end - pos);
        size_t colon = line.find(":");
        if (colon != std::string::npos)
        {
            std::string key = line.substr(0, colon);
            std::string value = line.substr(colon + 2);
            this->header[key] = value;
        }
        pos = end + 2;
    }
   
    // this->body = request.substr(pos, request.length() - pos);
    this->setBody(request.substr(pos + 2, request.length() - pos));
    // std::cout << "body " << this->body << std::endl;
    std::cout <<"dlk " << request.substr(pos + 2, request.length() - pos) << std::endl;
    return(request.substr(pos, request.length() - pos));
}

std::string ParseRequest::getLink()
{
    return (this->path);
}

void ParseRequest::affiche()
{
    std::cout << "------------------first line----------------------" << std::endl;
    std::cout << "Method: " << this->method << std::endl;
    std::cout << "Url: " << this->path << std::endl;
    std::cout << "HttpVersion: " << this->httpVersion << std::endl;
    std::cout << "-------------------header------------------------" << std::endl;
    for (std::map<std::string, std::string>::iterator it = this->header.begin(); it != this->header.end(); it++)
    {
        std::cout << it->first << ": " << it->second << std::endl;
    }
    std::cout << "-------------------body------------------------" << std::endl;
    std::cout << this->body << std::endl;
}

std::string ParseRequest::getMethod()
{
    return (this->method);
}

void ParseRequest::setBody(std::string body)
{
    for(size_t i = 0; i < body.size(); i++)
    {
        this->body.push_back(body[i]);
    }
}

std::string ParseRequest::getBody()
{
    return (this->body);
}

int ParseRequest::CheckHeader(int& status)
{
    if(!method.compare("DELETE"))
    {
        this->affiche();
    }
    std::string method = getMethod();
    if(method.compare("GET") == 0)
    {
        status = READYTO_RES;
    }
    else if(!method.compare("POST") || !method.compare("DELETE"))
    {
        if(getHeaders().find("Content-Length") != getHeaders().end())
        {
            if(toInt(getHeaders()["Content-Length"]) <= (int)this->body.size())
                status = READYTO_RES;
            return(content_length);
        }
        else if(getHeaders().find("Transfer-Encoding") != getHeaders().end())
        {
            if(getHeaders()["Transfer-Encoding"].compare("chunked") != 0)
                return(ERROR);
            else
                return(transfer_encoding);
        }
        else
        {
            if(!method.compare("POST"))
                return(ERROR);
            else
            {
                status = READYTO_RES;
            }
        }
        
    }
    return (NOT_ALLOWD_METHOD);
}

std::string ParseRequest::getPort()
{
    if (this->header.find("Host") == this->header.end())
        return ("");
    size_t pos = this->header["Host"].find(":");
    if (pos == std::string::npos)
        return ("");
    return ( this->header["Host"].substr(pos + 1));
}

std::string ParseRequest::getHost()
{
    if (this->header.find("Host") == this->header.end())
        return ("");
    size_t pos = this->header["Host"].find(":");
    if (pos == std::string::npos)
        return (this->header["Host"]);
    return (this->header["Host"].substr(0, pos));
}

std::string ParseRequest::getQuery()
{
    return (this->query);
}

std::map<std::string, std::string> ParseRequest::getHeaders()
{
    return (this->header);
}

std::string ParseRequest::getHeadr(std::string key)
{
    return (this->header[key]);
}

std::string		ParseRequest::parseFile()
{
    std::cout << this->body.substr(0, this->body.find("\r\n\r\n"));
    std::string s = this->body.substr(this->body.find("\r\n\r\n") + 4);
    std::string d = s.substr(0, s.find("\r\n\r\n") );
    // std::cout << "s " << d << std::endl;
    return (d);
}
#include "ParseRequest.hpp"

ParseRequest::ParseRequest() {}

void ParseRequest::parseRequest(const std::string &request)
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

    // parse header



    size_t pos = endOfLine + 2;
    while (pos < request.length())
    {
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
    ////std::cout << "-------------------body------------------------" << std::endl;
}

std::string ParseRequest::getMethod()
{
    return (this->method);
}

std::string ParseRequest::getHeadr(std::string key)
{
    return (this->header[key]);
}

std::map<std::string, std::string> ParseRequest::getHeaders()
{
    return (this->header);
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
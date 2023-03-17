#include "ParseRequest.hpp"

ParseRequest::ParseRequest() {}

void ParseRequest::parseRequest(const std::string &request)
{
    int endOfLine = request.find("\r\n");
    std::string firstLine = request.substr(0, endOfLine);
    int endOfMethod = firstLine.find(" ");
    int endOfUrl = firstLine.find(" ", endOfMethod + 1);

    this->method = firstLine.substr(0, endOfMethod);
    this->url = firstLine.substr(endOfMethod + 1, endOfUrl - endOfMethod - 1);
    this->httpVersion = firstLine.substr(endOfUrl + 1, firstLine.size() - endOfUrl - 1);

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
    return (this->url);
}
void ParseRequest::affiche()
{
    std::cout << "------------------first line----------------------" << std::endl;
    std::cout << "Method: " << this->method << std::endl;
    std::cout << "Url: " << this->url << std::endl;
    std::cout << "HttpVersion: " << this->httpVersion << std::endl;
    std::cout << "-------------------header------------------------" << std::endl;
    for (std::map<std::string, std::string>::iterator it = this->header.begin(); it != this->header.end(); it++)
    {
        std::cout << it->first << ": " << it->second << std::endl;
    }
    std::cout << "-------------------body------------------------" << std::endl;
}
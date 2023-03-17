
#pragma once
#include <iostream>
#include <map>

class ParseRequest
{
private:
    std::string method;
    std::string url;
    std::string httpVersion;
    std::map<std::string, std::string> header;
public:
    ParseRequest();
    void parseRequest(const std::string& request);
    std::string getLink();
    std::string getMethod();
    std::string getHeadr(std::string key);
    void affiche();
};
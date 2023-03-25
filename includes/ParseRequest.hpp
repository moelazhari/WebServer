
#pragma once
#include <iostream>
#include <map>

class ParseRequest
{
private:
    std::string method;
    std::string path;
    std::string query;
    std::string httpVersion;
    std::map<std::string, std::string> header;
public:
    ParseRequest();
    void parseRequest(const std::string& request);
    std::string getLink();
    std::string getMethod();
    std::string getHeadr(std::string key);
    std::string getPort();
    std::string getHost();
    std::string getQuery();
    void affiche();
};
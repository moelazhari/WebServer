
#pragma once
#include <iostream>
#include <map>
#include "define.hpp"
#include "utils.hpp"

class ParseRequest
{
private:
    std::string                         method;
    std::string                         url;
    std::string                         httpVersion;
    std::map<std::string, std::string>  header;
    std::string                         body;
public:
    ParseRequest();
    std::string                         parseRequest(const std::string& request);
    std::string                         getLink();
    std::string                         getMethod();
    void                                affiche();
    void                                setBody(std::string body);
    std::string                         getBody();
    std::map<std::string, std::string>  getHeader();
    int                                 CheckHeader(int& status);

};
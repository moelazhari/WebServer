#include <iostream>
#include <map>

class ParseRequest
{
private:
    std::string method;
    std::string url;
    std::string httpVersion;
    std::map<std::string, std::string> header;
    std::map<std::string, std::string> body;

public:
    ParseRequest();
    void parseRequest(const std::string& request);
    void affiche();
};
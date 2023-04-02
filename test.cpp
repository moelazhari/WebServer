#include <iostream>
#include <fstream> // for ifstream class
#include <unistd.h>

int main() {
    std::string body = "test_Upload-executable.test__hello";
    std::string test = "test";
    // std::cout << test + "__" << std::endl;
    size_t pos = body.find(test + "+_");
    if (pos == std::string::npos){
        std::cout << "not found" << std::endl;
        return(1);
    }
    std::string subgood = body.substr(pos);
    // std::string subbad = body.substr(body.find("walo"));

    std::cout << "subgood: " << subgood << std::endl;
    return 0;
}
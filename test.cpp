#include <iostream>
#include <string>
#include <sstream>

size_t hexToDec(std::string hex)
{
    int decimal;
    int i = 0;
    std::string hexa = "0123456789abcdef";
    while(i < hex.size())
    {
        if(hexa.find(hex[i]) == std::string::npos)
        {
            return -1;
        }
        i++;
    }
    std::stringstream ss;
    ss << hex;
    ss >> std::hex >> decimal;
    return decimal;
}

int main()
{
    std::string input = "5j\r\nHello\r\n6\r\nHello+\r\n0\r\n\r\n";
    std::string output = "";

    while(true)
    {
        size_t pos = input.find("\r\n");
        if(input.size() <= 4 && input.substr(0, 2).compare("0\r\n\r\n") != 0)
        {
            std::cout << "bad input" << std::endl;
            break;
        }
        if (pos == std::string::npos)
            break;
        std::string size = input.substr(0, pos);
        if(hexToDec(size) == -1 || hexToDec(size) > input.size())
        {
            std::cout << "Bad input" << std::endl;
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
            std::cout << "Bad input" << std::endl;
            break;
        }
        input = input.substr(2);
    }
        std::cout << "output: " << output << std::endl; 
    return 0;
}

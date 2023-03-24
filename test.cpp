#include <iostream>
#include <string>

const int BUFFER_SIZE = 5;

std::string readbuffer(std::string& body)
{
    if(body.size() > BUFFER_SIZE)
    {
        std::string buffer(body.begin(), body.begin() + BUFFER_SIZE);
        body.erase(body.begin(), body.begin() + BUFFER_SIZE);
        return buffer;
    }
    return body;
}

int main() {
    std::string data = "This is a large string object with lots of data......."; // large string object
    std::string::iterator pos;

    
      
while(data.size() > 5)
{
    ////std::cout << readbuffer(data) ;
}
////std::cout << readbuffer(data) ;
    return 0;
}
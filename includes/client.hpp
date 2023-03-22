#pragma one

#include "ParseRequest.hpp"
#include "response.hpp"
#include <poll.h>

class Client
{
    private:
        response _response;
        std::string _request;
        struct pollfd _fdClient;
        bool Readcomplete;
        bool isReadywrite;
        bool isReadclose;
    public:
        Client();
        ~Client();
        response &getResponse();
        pollfd &getFdClient();
        void setFdClient(struct pollfd fdClient);
};
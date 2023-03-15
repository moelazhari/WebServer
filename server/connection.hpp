#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
using namespace std;
// #define port 8003
#define MAX_CONNECTIONS 10
#define MAX_REQUEST_SIZE  1024
class Connection 
{
    private:
        int serverSocket;
        int clientSocket;
        int port;
        struct sockaddr_in serverAddr;
        struct sockaddr_in clientAddr;
    public:
        Connection(int port);
        void createsocket();
        void start();
        bool isReadyRead();
        bool isReadyWrite();
};

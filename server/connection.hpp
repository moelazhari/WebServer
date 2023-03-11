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
using namespace std;
#define port 8003
#define MAX_REQUEST_SIZE  1024
class Connection 
{
    private:
        int serverSocket;
        int clientSocket;
        struct sockaddr_in serverAddr;
        struct sockaddr_in clientAddr;
    public:
        void _socket();
        void _bind();
        void _accept();
        void _listen();
        void _recv();
        void print();
        void _send();
        void start();
};

#include "connection.hpp"

void Connection::_socket()
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        cerr << "Failed to create server socket" << endl;
        exit(1);
    }
    _bind();
}

void Connection::_bind()
{
    memset(&serverAddr, 0, sizeof(serverAddr));//clears the serverAddr struct variable to all zeros.
    serverAddr.sin_family = AF_INET; //AF_INET is the address family for IPv4
    //htons() converts the unsigned short integerfrom host byte order to network byte order.
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    serverAddr.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        cerr << "Failed to bind server socket to port " << port << endl;
        exit(1);
    }
    _listen();
}

void Connection::_listen()
{
    if (listen(serverSocket, 5) == -1) {
        cerr << "Failed to listen for incoming connections" << endl;
        exit(1);
    }
    start();
}

void Connection::_accept()
{
    socklen_t addrLen = sizeof(struct sockaddr_in);

    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);
    if (clientSocket == -1) {
        cerr << "Failed to accept incoming connection"<< endl;
        exit(1);
    }
    _recv();
}

void Connection::_recv()
{
    char request[MAX_REQUEST_SIZE];//normalement  object request parser
    int numBytes = recv(clientSocket, request, MAX_REQUEST_SIZE, 0);
    if (numBytes == -1) {
        cerr << "Failed to read request from client" << endl;
        close(clientSocket);
        exit(1);
    }
    cout << "Request: " << request << endl;//normalement  parse request
    _send();
   
}

void Connection::_send()
{

    const char* response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nHello World";
    if (send(clientSocket, response, strlen(response), 0) == -1) {
        cerr << "Failed to send response to client" << endl;
        exit(1);
    }
        cout <<"\n" <<response << endl;
    close(clientSocket);
}
void Connection::start()
{
    while (true) {
        cout << "Waiting for incoming connections port => "<< port << endl;
        _accept();
    }
    close(serverSocket);
}
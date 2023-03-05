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
#include "./requestParser/ParseRequest.hpp"

using namespace std;

const int MAX_REQUEST_SIZE = 1024;
const int DEFAULT_PORT = 8080;

int main(int argc, char *argv[]) {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(struct sockaddr_in);
    char request[MAX_REQUEST_SIZE];
    int port = DEFAULT_PORT;

    // Parse command line arguments
    if (argc > 1) {
        port = atoi(argv[1]);
    }

    // Create server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        cerr << "Failed to create server socket" << endl;
        exit(1);
    }

    // Bind server socket to port
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        cerr << "Failed to bind server socket to port " << port << endl;
        exit(1);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1) {
        cerr << "Failed to listen for incoming connections" << endl;
        exit(1);
    }

    // Accept incoming connections and handle requests
    while (true) {
        cout << "Waiting for incoming connections..." << endl;

        // Accept incoming connection
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);
        if (clientSocket == -1) {
            cerr << "Failed to accept incoming connection" << endl;
            continue;
        }

        // Read request from client
        int numBytes = recv(clientSocket, request, MAX_REQUEST_SIZE, 0);
        if (numBytes == -1) {
            cerr << "Failed to read request from client" << endl;
            close(clientSocket);
            continue;
        }

        // Print request information
        ParseRequest parseRequest;
        parseRequest.parseRequest(request);
        cout << "Request from client " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << endl;
        parseRequest.affiche();

        // Send response back to client
        const char* response = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\nHello World";
        if (send(clientSocket, response, strlen(response), 0) == -1) {
            cerr << "Failed to send response to client" << endl;
        }

        // Close client socket
        close(clientSocket);
    }

    // Close server socket
    close(serverSocket);

    return 0;
}
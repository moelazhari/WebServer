/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:57:31 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/05 14:55:39 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.hpp"

#define PORT 8000

using namespace std;
int main()
{
    // Create a TCP socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // Bind the socket to port 8000
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (sockaddr*)&server_address, sizeof(server_address)) < 0)
    	cerr << "setsockopt(SO_REUSEADDR) failed" << "\n";
    if (bind(server_socket, (sockaddr*)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Failed to bind socket to port " << PORT << std::endl;
		perror("Error: ");
        return 1;
    }

    // Start listening for incoming connections
    if (listen(server_socket, 10) < 0) {
        std::cerr << "Failed to listen on socket" << std::endl;
        return 1;
    }

    std::cout << "Server started on port " << PORT << std::endl;

	int request = 0;
    while (true) {
        // Accept a new connection
        sockaddr_in client_address;
        socklen_t client_address_length = sizeof(client_address);
        int client_socket = accept(server_socket, (sockaddr*)&client_address, &client_address_length);
        if (client_socket < 0) {
            std::cerr << "Failed to accept connection" << std::endl;
            continue;
        }

        // Read the client's request
        char buffer[1024] = {0};
        int bytes_read = read(client_socket, buffer, sizeof(buffer));
		if (bytes_read > 0) {
			cout << "Request: " << ++request << endl;
		}
        else{
            std::cerr << "Failed to read from socket" << std::endl;
            close(client_socket);
            continue;
        }

        // Send a response back to the client
        const char* response = "HTTP/1.1 200 OK\r\nDate: Sat, 09 Oct 2010 14:28:02 GMT\r\nLast-Modified: Tue, 01 Dec 2009 20:18:22 GMT\r\nETag: 51142bc1-7449-479b075b2891b\r\nAccept-Ranges: bytes\r\nContent-Length: 29769\r\nContent-Type: text/html\r\n\r\n <h1>socket is working</h1>\r\n";
		int bytes_written;
        bytes_written = write(client_socket, response, strlen(response));
        // bytes_written = write(client_socket, buffer, strlen(buffer));
        ofstream out;
        out.open("request.html");
        out << buffer << endl;
        if (bytes_written < 0) {
            std::cerr << "Failed to write to socket" << std::endl;
        }

        // Close the connection
        close(client_socket);
    }

    // Close the server socket
    close(server_socket);

    return 0;
}



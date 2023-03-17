#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>

using namespace std;

#define MAX_CLIENTS 10

int main()
{
    int opt = 1;
    int i, activity, valread, new_socket;
    int master_socket[MAX_CLIENTS], addrlen, sd;
    vector<int> clients;
    struct sockaddr_in address[MAX_CLIENTS];
    char buffer[1025] = {0};
    struct pollfd fds[MAX_CLIENTS];

    // Create a master socket for each port
    for (i = 0; i < MAX_CLIENTS; i++)
    {
        if ((master_socket[i] = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        // Allow multiple connections
        if (setsockopt(master_socket[i], SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
        {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }

        // Bind the socket to localhost with different port numbers
        address[i].sin_family = AF_INET;
        address[i].sin_addr.s_addr = INADDR_ANY;
        address[i].sin_port = htons(8080 + i);

        if (bind(master_socket[i], (struct sockaddr *)&address[i], sizeof(address[i])) < 0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }

        // Listen for incoming connections
        if (listen(master_socket[i], 3) < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }

        // Add master socket to pollfd structure
        fds[i].fd = master_socket[i];
        fds[i].events = POLLIN;
    }

    addrlen = sizeof(address[0]);

    while (true)
    {
        // Call poll function to monitor multiple sockets
        activity = poll(fds, MAX_CLIENTS, -1);
        if (activity < 0)
        {
            perror("poll failed");
            exit(EXIT_FAILURE);
        }

        for (i = 0; i < MAX_CLIENTS; i++)
        {
            // Check if there is any activity on the current socket
            if (fds[i].revents & POLLIN)
            {
                // Check if this activity is on the master socket, indicating a new connection
                if (fds[i].fd == master_socket[i])
                {
                    if ((new_socket = accept(master_socket[i], (struct sockaddr *)&address[i], (socklen_t *)&addrlen)) < 0)
                    {
                        perror("accept");
                        exit(EXIT_FAILURE);
                    }

                    // Add new socket to clients vector and pollfd structure
                    clients.push_back(new_socket);
                    fds[clients.size() - 1].fd = new_socket;
                    fds[clients.size() - 1].events = POLLIN;

                    cout << "New connection: socket fd = " << new_socket << ", port = " << ntohs(address[i].sin_port) << ", ip = " << inet_ntoa(address[i].sin_addr) << endl;
                }
                else
                {
                    // Activity on a client socket
                    sd = fds[i].fd;

                    if ((valread = read(sd, buffer, 1024)) == 0)
                    {
                        // Client disconnected
                        close(sd);
                        clients.erase(clients.begin() + i);
                        fds[i].fd = -1;
                    }
                    else
                    {
                        // Echo back the received message to the client
                        buffer[valread] = '\0';
                        send(sd, buffer, strlen(buffer), 0);
                    }
                }
            }
        }
    }

    return 0;
}

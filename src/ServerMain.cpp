#include "Server_regular_engineer_thread_class.hpp" 
#include "ServerExpertThreadPool.hpp"
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <vector>

void bindAddress(int serverSocket, int port) {
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

     if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error binding server socket");
        close(serverSocket);
        
    }
    
}

void listenAddress(int serverSocket)
{
   if (listen(serverSocket, 200) == -1) {
        perror("Error listening for connections");
        close(serverSocket);
    }
}

int main(int argc, char *argv[]) {
    int port;
    int numExperts = 5;
    if (argc == 2) {   
        port = std::stoi(argv[1]);
    }
    else {

        port = std::stoi(argv[1]);
        numExperts = std::stoi(argv[2]);
    } 
    // Create a server socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating server socket");
        return 1;
    }

    bindAddress(serverSocket, port);
    listenAddress(serverSocket);

    ThreadPool expertThreadPool(numExperts);
    std::vector<std::unique_ptr<ServerRegularEngineerThreadClass>> engineers;
    int connectedCLient = 0;

    while (true) {
        struct sockaddr_in clientAddress;
        socklen_t clientAddrSize = sizeof(clientAddress);
        int connectedSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddrSize);
        if (connectedSocket == -1) {
            perror("Error accepting connection");
            continue; 
        }
        engineers.push_back(std::unique_ptr<ServerRegularEngineerThreadClass>
        (new ServerRegularEngineerThreadClass(expertThreadPool, connectedCLient)));
        engineers.back()->createThread(connectedSocket);
         ++connectedCLient;
    }

    for (auto& engineer : engineers) {
        engineer->stopThread(); // Signal the thread to stop
    }


     for (int i = 0; i < engineers.size(); i++) {
        if (engineers[i]->regularEngineerThread.joinable()) {
                engineers[i]->regularEngineerThread.join();
        }
     }

    return 0;
}

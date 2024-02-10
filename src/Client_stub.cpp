#include "Client_stub.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

void ClientStub::Init(const std::string& ip, int port) {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr);
    connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
}

LaptopInfo ClientStub::Order(const Orders& order) {
   
    std::vector<char> buffer(sizeof(order));
    std::memcpy(buffer.data(), &order, sizeof(order));
    send(clientSocket, buffer.data(), buffer.size(), 0);
    LaptopInfo laptopInfo;
    std::vector<char> buffer2(sizeof(LaptopInfo));
    recv(clientSocket, buffer2.data(), buffer2.size(), 0);
    std::memcpy(&laptopInfo, buffer2.data(), sizeof(LaptopInfo));

    return laptopInfo;
}

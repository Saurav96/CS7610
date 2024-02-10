#include "Server_stub.hpp"

void ServerStub::Init(int connectedSocket) {
    serverSocket = connectedSocket;
}

Orders ServerStub::ReceiveOrder() {
    Orders order;
    char buffer[sizeof(Orders)];
    recv(serverSocket, &buffer, sizeof(Orders), 0);
    memcpy(&order, buffer, sizeof(Orders));
    return order;
}

void ServerStub::ShipLaptop(const LaptopInfo& laptopInfo) {
    char buffer[sizeof(LaptopInfo)];
    memcpy(buffer, &laptopInfo, sizeof(LaptopInfo));
    send(serverSocket, &buffer, sizeof(LaptopInfo), 0);
}


#ifndef SERVER_STUB_HPP
#define SERVER_STUB_HPP

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include "Orders.hpp"
#include "LaptopInfo.hpp"

class ServerStub {
public:
    int serverSocket;

    void Init(int connectedSocket);
    Orders ReceiveOrder();
    void ShipLaptop(const LaptopInfo& laptopInfo);
};


#endif // SERVER_STUB_HPP


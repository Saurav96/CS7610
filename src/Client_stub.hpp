#ifndef CLIENT_STUB_HPP
#define CLIENT_STUB_HPP

#include "Orders.hpp"
#include "LaptopInfo.hpp"
#include <string>

class ClientStub {
public:
    int clientSocket;

    void Init(const std::string& ip, int port);
    LaptopInfo Order(const Orders& order);
};

#endif

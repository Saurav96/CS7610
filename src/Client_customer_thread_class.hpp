#ifndef CUSTOMER_THREAD_CLASS_HPP
#define CUSTOMER_THREAD_CLASS_HPP

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <vector>
#include "Client_stub.hpp"

class CustomerClass
{

public:
    std::thread threadPtr;
    std::vector<long> executionTimes;
    ClientStub clientStub;

    CustomerClass();

    void customerThread(std::string ip, int port, int customerId, int numOrders, int laptopType);

    void createThread(std::string ip, int port, int i, int numOrdersPerCustomer, int laptopTypes);
};

#endif

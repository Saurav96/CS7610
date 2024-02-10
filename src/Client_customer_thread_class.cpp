#include "Client_customer_thread_class.hpp"

CustomerClass::CustomerClass() {}

void CustomerClass::customerThread(std::string ip, int port, int customerId, int numOrders, int laptopType)
{
    clientStub.Init(ip, port); // Initialize the ClientStub for each thread
   for (int i = 1; i <= numOrders; ++i)
    {
    auto start_time = std::chrono::high_resolution_clock::now();
    Orders order(customerId, i, laptopType);
    LaptopInfo laptopInfo = clientStub.Order(order);
    auto end_time = std::chrono::high_resolution_clock::now();
    long time_taken = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    executionTimes.emplace_back(time_taken);
    }
    
    //close(clientStub.clientSocket);

}

void CustomerClass::createThread(std::string ip, int port, int i, int numOrdersPerCustomer, int numOfTypes)
{
    threadPtr = std::thread([this, ip, port, i, numOrdersPerCustomer, numOfTypes]() {
        customerThread(ip, port, i, numOrdersPerCustomer, numOfTypes);
    });
}


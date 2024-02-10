#include <iostream>
#include <vector>
#include <memory>
#include "Client_customer_thread_class.hpp"

int main(int argc, char *argv[])
{
    if (argc != 6) {
        std::cerr << "Usage: " << argv[0] << " [ip addr] [port #] [# customers] [# orders] [laptop type]\n";
        return 1;
    }

    std::string ip = argv[1];
    int port = std::stoi(argv[2]);
    int totalCustomers = std::stoi(argv[3]);
    int numOrders = std::stoi(argv[4]);
    int laptopType = std::stoi(argv[5]);
   
    std::vector<std::unique_ptr<CustomerClass>> customerThreads;

    int i = 0;
    while(i<totalCustomers)
    {
        customerThreads.emplace_back(std::unique_ptr<CustomerClass>(new CustomerClass()));
        customerThreads.back()->createThread(ip, port, i, numOrders, laptopType);
        ++i;
    }

    for (auto& customer : customerThreads) {
        customer->threadPtr.join();
    }

    int totalOrders = 0;
    for (const auto& customer : customerThreads) {
        std::cout << "Customer " << totalOrders + 1 << " average time: " << customer->executionTimes.size() << std::endl;
        for (const auto& time : customer->executionTimes) {
            std::cout << time << std::endl;
        }
        totalOrders += customer->executionTimes.size();
        std::cout << "Total time: " << totalOrders << std::endl;
    }


    return 0;
}

#include "Server_regular_engineer_thread_class.hpp"

ServerRegularEngineerThreadClass::ServerRegularEngineerThreadClass(ThreadPool &pool, int id) 
    : poolThread(pool) , engineerID(id)  {} // Initialize poolThread in constructor initializer list

ServerRegularEngineerThreadClass::ServerRegularEngineerThreadClass(ThreadPool &pool) 
    : poolThread(pool), engineerID(0)  {} // Initialize poolThread in constructor initializer list

void ServerRegularEngineerThreadClass::serverThread(int connectedSocket)
{
    stub.Init(connectedSocket);
    while (keepRunning)
    {
        Orders order = stub.ReceiveOrder();

         if (!keepRunning) // Check if we should exit
            break;

        if (order.laptop_type == 1) {
            auto future = poolThread.enqueueOrder(order);
            LaptopInfo laptopInfo = future.get();
            laptopInfo.engineer_id = engineerID;
            stub.ShipLaptop(laptopInfo);
        } else {
            LaptopInfo laptopInfo(order.customer_id, order.order_number, order.laptop_type, engineerID, -1);
            stub.ShipLaptop(laptopInfo);
        }

        LaptopInfo laptopInfo(order.customer_id, order.order_number, order.laptop_type, engineerID,-1);
        stub.ShipLaptop(laptopInfo);
    }
}

void ServerRegularEngineerThreadClass::stopThread() {
    keepRunning = false;
}

void ServerRegularEngineerThreadClass::createThread(int connectedSocket)
{
    regularEngineerThread = std::thread([this, connectedSocket]() {
        this->serverThread(connectedSocket);
    });
}

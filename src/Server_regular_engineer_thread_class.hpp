#ifndef SERVERREGULARENGINEERTHREADCLASS_HPP
#define SERVERREGULARENGINEERTHREADCLASS_HPP

#include "Server_stub.hpp" // Include necessary dependencies
#include<thread>
#include "ServerExpertThreadPool.hpp"
class ServerRegularEngineerThreadClass
{ 

private:
    std::atomic<bool> keepRunning{true};
    ThreadPool &poolThread;

public:
    int engineerID;
    ServerStub stub;
    std::thread regularEngineerThread;

    ServerRegularEngineerThreadClass(ThreadPool &pool);
    ServerRegularEngineerThreadClass(ThreadPool &pool, int id);
    void serverThread(int connectedSocket);
    void createThread(int connectedSocket);
    void stopThread();

};

#endif // REGULARENGINEERTHREADCLASS_HPP

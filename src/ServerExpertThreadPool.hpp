// ExpertThreadPool.hpp
#ifndef EXPERTTHREADPOOL_HPP
#define EXPERTTHREADPOOL_HPP

#include <vector>
#include <thread>
#include<iostream>
#include <future>
#include <functional>
#include <queue>
#include "ServerExpert.hpp"
#include "ServerOrderQueue.hpp"

class ThreadPool {
public:
    ThreadPool(size_t numExperts);
    ~ThreadPool();
    std::future<LaptopInfo> enqueueOrder(const Orders &order);

private:
    std::vector<std::thread> expertThreads;
    OrderQueue orderQueue;
    bool stop;
    ServerExpert expert;
    void threadTask(int id);
};


#endif // EXPERTTHREADPOOL_HPP

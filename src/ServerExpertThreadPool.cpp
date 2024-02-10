#include "ServerExpertThreadPool.hpp"

ThreadPool::ThreadPool(size_t numExperts) : stop(false) {
    for (size_t i = 0; i < numExperts; ++i) {
        expertThreads.emplace_back(&ThreadPool::threadTask, this, i);
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(orderQueue.getMutex());
        stop = true;
    }
    orderQueue.notifyAll();
    for (auto &thread : expertThreads) {
        thread.join();
    }
}

std::future<LaptopInfo> ThreadPool::enqueueOrder(const Orders &order) {
    std::future<LaptopInfo> future = orderQueue.pushOrder(order);
    
    // Return the future to the caller
    return future;
}

void ThreadPool::threadTask(int id) {
    while (true) {
        Orders order = orderQueue.popOrder();
        if (stop && orderQueue.isEmpty()) {
            break;
        }
        expert.customLaptopOrder(order);
        // Do something with the laptop result
        // For now, just print the expert ID
        std::cout << "Laptop processed by Expert " << id << std::endl;
    }
    
}

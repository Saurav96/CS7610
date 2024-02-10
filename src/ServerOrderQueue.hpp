#ifndef ORDERQUEUE_HPP
#define ORDERQUEUE_HPP

#include <future>
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include "Orders.hpp" // Include the Order class header file
#include "LaptopInfo.hpp"

class OrderQueue {
public:
    using PromisePtr = std::shared_ptr<std::promise<LaptopInfo>>;
    using Future = std::future<LaptopInfo>;

    Future pushOrder(const Orders& order);
    Orders popOrder();
    bool isEmpty() const;
    void notifyAll();
    std::mutex& getMutex();

private:
    std::queue<Orders> orders;
    std::queue<PromisePtr> promises;
    mutable std::mutex mutex;
    std::condition_variable cv;
};

#endif // ORDERQUEUE_HPP

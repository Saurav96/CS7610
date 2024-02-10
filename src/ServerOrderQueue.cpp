#include "ServerOrderQueue.hpp"

OrderQueue::Future OrderQueue::pushOrder(const Orders& order) {
    std::unique_lock<std::mutex> lock(mutex);
    PromisePtr promisePtr = std::make_shared<std::promise<LaptopInfo>>();
    Future future = promisePtr->get_future();
    promises.push(promisePtr);
    orders.push(order);
    cv.notify_one();
    return future;
}

Orders OrderQueue::popOrder() {
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [this]() { return !orders.empty(); });
    Orders order = orders.front();
    orders.pop();
    return order;
}

bool OrderQueue::isEmpty() const {
    std::unique_lock<std::mutex> lock(mutex);
    return orders.empty();
}

void OrderQueue::notifyAll() {
    cv.notify_all();
}

std::mutex& OrderQueue::getMutex() {
    return mutex;
}

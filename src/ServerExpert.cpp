// Expert.cpp
#include "ServerExpert.hpp"

LaptopInfo ServerExpert::customLaptopOrder(const Orders& order) {
    // Implement custom logic for processing custom orders
    // For example, sleep for some time to simulate processing
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // Then return the processed laptop
    return LaptopInfo(order.customer_id, order.order_number, order.laptop_type, -1, -1);
}

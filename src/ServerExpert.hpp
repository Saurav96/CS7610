// Expert.hpp
#ifndef SERVER_EXPERT_HPP
#define SERVER_EXPERT_HPP

#include "Orders.hpp"
#include "LaptopInfo.hpp"
#include<chrono>
#include<thread>

class ServerExpert {
public:
    LaptopInfo customLaptopOrder(const Orders& order);
};

#endif // EXPERT_HPP

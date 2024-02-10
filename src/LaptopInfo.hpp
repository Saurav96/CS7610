#ifndef LAPTOP_INFO_HPP
#define LAPTOP_INFO_HPP

struct LaptopInfo {
    int customer_id;
    int order_number;
    int laptop_type;
    int engineer_id;
    int expert_id;

    LaptopInfo() : customer_id(-99), order_number(-99), laptop_type(-99), engineer_id(-99), expert_id(-99) {}

    LaptopInfo(int customer, int order, int type, int engineer, int expert)
        : customer_id(customer), order_number(order), laptop_type(type),
          engineer_id(engineer), expert_id(expert) {}
};

#endif  // LAPTOP_INFO_HPP

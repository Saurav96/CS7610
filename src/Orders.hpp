#pragma once

struct Orders {
    int customer_id;
    int order_number;
    int laptop_type;

    Orders() : customer_id(-99), order_number(-99), laptop_type(-99) {}
    Orders(int customer, int order, int type) : customer_id(customer), order_number(order), laptop_type(type) {}
};



#pragma once


#include <memory>
#include <unordered_set>
#include "Order.h"

typedef std::unordered_set<Order, Order::HashFunction> OrderSet;
typedef std::shared_ptr<std::unordered_set<Order, Order::HashFunction>> OrderSetPtr;

class Cache {
public:
    Cache();

    void addOrder(const Order& order_);
    void cancelByOrderId(const std::string& orderId_);
    void cancelByUserId(const std::string& userId_);
    void cancelBySecurityId(const std::string& securityId_, int quantity_);
    double match(std::string securityId_);

    const OrderSetPtr &getOrders() const;


private:
    OrderSetPtr _orders;

};

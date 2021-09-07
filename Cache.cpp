#include <boost/log/trivial.hpp>
#include <sstream>
#include <vector>
#include <iostream>
#include "Cache.h"

Cache::Cache() {
    _orders = std::make_shared<OrderSet>();
}

void Cache::addOrder(const Order& order_) {
    bool inserted;
    std::tie(std::ignore, inserted) = _orders->insert(order_);
    if (!inserted) {
        std::ostringstream errMsg;
        errMsg << "Order with the following ID already exists: " << order_.getOrderId();
        throw std::invalid_argument(errMsg.str());
    }
}

void Cache::cancelByOrderId(const std::string& orderId_) {
    if (_orders->erase(Order(orderId_)) == 0) {
        std::ostringstream errMsg;
        errMsg << "Order with the following ID does not exists: " << orderId_;
        throw std::invalid_argument(errMsg.str());
    }
}

void Cache::cancelByUserId(const std::string& userId_) {
    for (auto it = _orders->begin(), last = _orders->end(); it != last; ) {
        if (it->getUserId() == userId_) {
            it = _orders->erase(it);
        } else {
            ++it;
        }
    }
}

void Cache::cancelBySecurityId(const std::string& securityId_, int quantity_) {
    for (auto it = _orders->begin(), last = _orders->end(); it != last; ) {
        if (it->getSecurityId() == securityId_ && it->getQuantity() >= quantity_) {
            it = _orders->erase(it);
        } else {
            ++it;
        }
    }
}

double Cache::match(std::string securityId_) {
    std::vector<Order> buys, sells;
    double matchedTotal = 0;
    for (auto it = _orders->begin(); it != _orders->end(); ++it ) {
        if (it->getSecurityId() == securityId_) {
            if (it->getSide().getType() == Order::Side::BUY)
                buys.push_back(*it);
            else if (it->getSide().getType() == Order::Side::SELL)
                sells.push_back(*it);
            else {
                std::ostringstream errMsg;
                errMsg << "Order with ID " << it->getOrderId() << "has an invalid side";
                throw std::logic_error(errMsg.str());
            }
        }
    }

    for (auto sellIt = sells.begin(); sellIt != sells.end() ; ++sellIt) {
        for (auto buyIt = buys.begin(); buyIt != buys.end() ; ++buyIt) {
            if (sellIt->getCompany() != buyIt->getCompany()) {
                double matched = std::min(sellIt->getQuantity(), buyIt->getQuantity());
                matchedTotal += matched;
                sellIt->setQuantity(sellIt->getQuantity()-matched);
                buyIt->setQuantity(buyIt->getQuantity()-matched);
            }
        }
    }
    return matchedTotal;
}

const OrderSetPtr &Cache::getOrders() const {
    return _orders;
}

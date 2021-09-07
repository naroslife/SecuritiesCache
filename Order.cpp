#include <boost/algorithm/string.hpp>
#include <exception>
#include "Order.h"

Order::Order(const std::string &orderId_, const std::string &securityId_, const std::string &userId_,
             const std::string &company_, Order::Side side_, int quantity_) : _orderId(orderId_), _securityId(securityId_),
                                                                              _userId(userId_), _company(company_), _side(side_),
                                                                              _quantity(quantity_) {}

Order::Order(const std::string &orderId_, const std::string &securityId_, const std::string &userId_,
             const std::string &company_, std::string side_, int quantity_) : _orderId(orderId_), _securityId(securityId_),
                                                                              _userId(userId_), _company(company_), _side(side_),
                                                                              _quantity(quantity_) {}

Order::Order(const std::string &orderId_, const std::string &securityId_, const std::string &userId_,
             const std::string &company_, Order::Side::EType side_, int quantity_) : _orderId(orderId_), _securityId(securityId_),
                                                                                     _userId(userId_), _company(company_), _side(side_),
                                                                                     _quantity(quantity_) {}

Order::~Order() {

}

bool Order::operator==(const Order &rhs) const {
    return _orderId == rhs._orderId;
}

bool Order::operator!=(const Order &rhs) const {
    return !(rhs == *this);
}

const std::string &Order::getOrderId() const {
    return _orderId;
}

void Order::setOrderId(const std::string &orderId) {
    _orderId = orderId;
}

const std::string &Order::getSecurityId() const {
    return _securityId;
}

void Order::setSecurityId(const std::string &securityId) {
    _securityId = securityId;
}

const std::string &Order::getUserId() const {
    return _userId;
}

void Order::setUserId(const std::string &userId) {
    _userId = userId;
}

const std::string &Order::getCompany() const {
    return _company;
}

void Order::setCompany(const std::string &company) {
    _company = company;
}

const Order::Side &Order::getSide() const {
    return _side;
}

void Order::setSide(const Order::Side &side) {
    _side = side;
}

int Order::getQuantity() const {
    return _quantity;
}

void Order::setQuantity(int quantity) {
    _quantity = quantity;
}


Order::Side::EType Order::Side::stringToType(const std::string &typeStr_) {
    const std::string &strLower = boost::algorithm::to_lower_copy(typeStr_);
    if (strLower == "buy")
        return BUY;
    else if (strLower == "sell")
        return SELL;
    else throw std::invalid_argument("Side has to be either buy or sell.");
}

std::string const Order::Side::typeToString(Order::Side::EType type_) {
    switch (type_) {
        case BUY: return "BUY"; break;
        case SELL: return "SELL"; break;
        default: throw std::invalid_argument("Side has to be either buy or sell.");
    }
}

Order::Side::EType Order::Side::getType() const {
    return _type;
}

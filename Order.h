#pragma once
#include <string>

class Order {
public:

    class Side {
    public:
        enum EType {UNDEFINED, BUY, SELL};
        Side():_type(UNDEFINED){};
        Side(std::string const& typeStr_):_type(stringToType(typeStr_)){};
        Side(EType type_):_type(type_){};

        EType getType() const;

    private:
        static EType stringToType (const std::string& typeStr_);
        static std::string const typeToString(EType type_);

        EType _type;
    };

    Order(const std::string &orderId_, const std::string &securityId_="", const std::string &userId_="",
          const std::string &company_="", Side side_= Side(Order::Side::UNDEFINED), int quantity_=0);
    Order(const std::string &orderId_, const std::string &securityId_, const std::string &userId_,
          const std::string &company_, std::string side_, int quantity_);
    Order(const std::string &orderId_, const std::string &securityId_, const std::string &userId_,
          const std::string &company_, Side::EType side_, int quantity_);
    virtual ~Order();

    const std::string &getOrderId() const;

    void setOrderId(const std::string &orderId);

    const std::string &getSecurityId() const;

    void setSecurityId(const std::string &securityId);

    const std::string &getUserId() const;

    void setUserId(const std::string &userId);

    const std::string &getCompany() const;

    void setCompany(const std::string &company);

    const Side &getSide() const;

    void setSide(const Side &side);

    int getQuantity() const;

    void setQuantity(int quantity);

    bool operator==(const Order &rhs) const;
    bool operator!=(const Order &rhs) const;
    struct HashFunction
    {
        size_t operator()(const Order& order_) const
        {
            return std::hash<std::string>()(order_._orderId);
        }
    };

private:
    std::string _orderId;
    std::string _securityId;
    std::string _userId;
    std::string _company;
    Side _side;
    int _quantity;




};

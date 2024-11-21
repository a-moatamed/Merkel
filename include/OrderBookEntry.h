#pragma once
#include<string>
// define a new data type with 2 values bid and ask
enum class OrderBookType {bid, ask, unkown, asksale, bidsale};

// define the OrderBookEntry class
class OrderBookEntry
{
public:
    // define the constructor of the class using member initializer list
    OrderBookEntry(
        double _price,
        double _amount,
        std::string _timestamp,
        std::string _product,
        OrderBookType _orderType,
        std::string username = "dataset");

    //define a function to convert the string to OrderBookType(either bid or ask)
    static OrderBookType stringToOrderBookType(std::string s);

    /**Custom Function to sort the object entered by the user*/
    // this is a very intreasted senario to put the implementation into the header file
    static bool compareByTimestamp(const OrderBookEntry &e1, const OrderBookEntry &e2)
    {
        return e1.timestamp < e2.timestamp;
    }
    static bool compareByPriceAsc(OrderBookEntry &e1, OrderBookEntry &e2)
    {
        return e1.price < e2.price;
    }
    static bool compareByPriceDesc(OrderBookEntry &e1, OrderBookEntry &e2)
    {
        return e1.price > e2.price;
    }

    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
    std::string username;
};
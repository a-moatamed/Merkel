#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(
    double _price,
    double _amount,
    std::string _timestamp,
    std::string _product,
    OrderBookType _orderType,
    std::string _username)
    : price(_price),
      amount(_amount),
      timestamp(std::move(_timestamp)),
      product(std::move(_product)),
      orderType(_orderType),
      username(std::move(_username))
{
}

OrderBookType OrderBookEntry::stringToOrderBookType(const std::string& s)
{
    if (s == "ask") {
        return OrderBookType::ask;
    } 
    else if (s == "bid") {
        return OrderBookType::bid;
    } 
    else
    {
      return OrderBookType::unkown; // set it as unkown if it's not bid or ask
    }
}

bool OrderBookEntry::compareByTimestamp(const OrderBookEntry& e1, const OrderBookEntry& e2)
{
    return e1.timestamp < e2.timestamp;
}

bool OrderBookEntry::compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2)
{
    return e1.price < e2.price;
}

bool OrderBookEntry::compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2)
{
    return e1.price > e2.price;
}

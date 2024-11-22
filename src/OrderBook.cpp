#include "OrderBook.h"
#include <algorithm>
#include <iostream>

/** Constructor, reading a CSV data file */
OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
}

/** Return vector of all products in the dataset */
std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;
    std::map<std::string, bool> prodMap;

    // Collect unique product names from all orders
    for (const OrderBookEntry &e : orders)
    {
        prodMap[e.product] = true;
    }

    // Copy the keys (product names) from the map to the products vector
    for (const auto &e : prodMap)
    {
        products.push_back(e.first);
    }

    return products;
}

/** Return vector of Orders according to the given filters */
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                                 std::string product,
                                                 std::string timestamp)
{
    std::vector<OrderBookEntry> orders_sub;

    // Filter orders by type, product, and timestamp
    for (const OrderBookEntry &e : orders)
    {
        if (e.orderType == type && e.product == product && e.timestamp == timestamp)
        {
            orders_sub.push_back(e);
        }
    }

    return orders_sub;
}

/** Return the highest price from a list of orders */
double OrderBook::getHighPrice(std::vector<OrderBookEntry> &orders)
{
    if (orders.empty()) return 0.0;  // Handle empty orders safely

    double max = orders[0].price;
    for (const OrderBookEntry &e : orders)
    {
        max = std::max(max, e.price);  // Use std::max for efficiency
    }

    return max;
}

/** Return the lowest price from a list of orders */
double OrderBook::getLowPrice(std::vector<OrderBookEntry> &orders)
{
    if (orders.empty()) return 0.0;  // Handle empty orders safely

    double min = orders[0].price;
    for (const OrderBookEntry &e : orders)
    {
        min = std::min(min, e.price);  // Use std::min for efficiency
    }

    return min;
}

/** Return the earliest timestamp in the orderbook */
std::string OrderBook::getEarliestTime()
{
    return orders.empty() ? "" : orders[0].timestamp;  // Handle empty orders safely
}

/** Return the next timestamp after the given timestamp */
std::string OrderBook::getNextTime(std::string timestamp)
{
    if (orders.empty()) return "";  // Handle empty orders safely

    std::string next_timestamp = "";
    for (const OrderBookEntry &e : orders)
    {
        if (e.timestamp > timestamp)
        {
            next_timestamp = e.timestamp;
            break;  // Exit loop once the next timestamp is found
        }
    }

    return next_timestamp.empty() ? orders[0].timestamp : next_timestamp;  // Return the first timestamp if no match found
}

/** Insert a new order into the orderbook */
void OrderBook::insertOrder(OrderBookEntry &order)
{
    orders.push_back(order);  // Add the order to the vector
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);  // Sort the orders by timestamp
}

/** Match asks to bids and return sales */
std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);
    std::vector<OrderBookEntry> sales;

    // Ensure there are both asks and bids to process
    if (asks.empty() || bids.empty())
    {
        std::cout << "OrderBook::matchAsksToBids no bids or asks" << std::endl;
        return sales;
    }

    // Sort asks (lowest price first) and bids (highest price first)
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);
    std::cout << "max ask " << asks[asks.size() - 1].price << std::endl;
    std::cout << "min ask " << asks[0].price << std::endl;
    std::cout << "max bid " << bids[0].price << std::endl;
    std::cout << "min bid " << bids[bids.size() - 1].price << std::endl;


    // Iterate through asks and bids to match them
    for (OrderBookEntry &ask : asks)
    {
        for (OrderBookEntry &bid : bids)
        {
            // If the bid price is greater than or equal to the ask price, we have a match
            if (bid.price >= ask.price)
            {
                OrderBookEntry sale{ask.price, 0, timestamp, product, OrderBookType::asksale};

                // Assign the user to the sale
                if (bid.username == "simuser")
                {
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::bidsale;
                }
                if (ask.username == "simuser")
                {
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::asksale;
                }

                // Handle different cases for the sale amount
                if (bid.amount == ask.amount)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0;  // Bid is completely used
                    break;  // Move on to the next ask
                }
                if (bid.amount > ask.amount)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount -= ask.amount;  // Reduce the bid amount
                    break;  // Move on to the next ask
                }
                if (bid.amount < ask.amount && bid.amount > 0)
                {
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount -= bid.amount;  // Reduce the ask amount
                    bid.amount = 0;  // Bid is completely used
                    continue;  // Move on to the next bid
                }
            }
        }
    }

    return sales;
}

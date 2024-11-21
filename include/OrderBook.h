#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <math.h>
#include <algorithm>

/**
 * @class OrderBook
 * @brief This class manages the order book, which holds orders and handles the matching of bids and asks.
 * 
 * The `OrderBook` class provides methods for reading orders from a CSV file, retrieving orders based on filters,
 * matching ask and bid orders, and managing the order book's data.
 */
class OrderBook
{
public:
    /**
     * @brief Constructor that reads order data from a CSV file.
     * 
     * This constructor initializes the `OrderBook` by loading order data from the specified CSV file.
     * The orders are read into the internal `orders` vector using the `CSVReader`.
     * 
     * @param filename The name of the CSV file containing order data.
     */
    OrderBook(std::string filename);

    /**
     * @brief Returns a vector of all unique product names in the order book.
     * 
     * This method iterates through the order book and extracts the unique product names.
     * 
     * @return A vector of product names.
     */
    std::vector<std::string> getKnownProducts();
    
    /**
     * @brief Returns a filtered list of orders based on the specified criteria.
     * 
     * This method filters the orders based on order type (ask or bid), product, and timestamp.
     * 
     * @param type The order type (ask or bid).
     * @param product The product name to filter orders by.
     * @param timestamp The timestamp to filter orders by.
     * 
     * @return A vector of orders that match the given filters.
     */
    std::vector<OrderBookEntry> getOrders(OrderBookType type,
                                          std::string product,
                                          std::string timestamp);

    /**
     * @brief Returns the earliest timestamp in the order book.
     * 
     * This method retrieves the earliest timestamp based on the order list.
     * 
     * @return The earliest timestamp as a string.
     */
    std::string getEarliestTime();

    /**
     * @brief Returns the next timestamp that occurs after the provided timestamp.
     * 
     * This method searches the order book for the next timestamp after the provided one. 
     * If no next timestamp is found, it wraps around and returns the first timestamp.
     * 
     * @param timestamp The current timestamp to compare against.
     * 
     * @return The next timestamp in the order book.
     */
    std::string getNextTime(std::string timestamp);

    /**
     * @brief Returns the highest price among the provided orders.
     * 
     * This static method scans the provided orders and returns the highest price.
     * 
     * @param orders A vector of orders to search through.
     * 
     * @return The highest price from the provided orders.
     */
    static double getHighPrice(std::vector<OrderBookEntry> &orders);

    /**
     * @brief Returns the lowest price among the provided orders.
     * 
     * This static method scans the provided orders and returns the lowest price.
     * 
     * @param orders A vector of orders to search through.
     * 
     * @return The lowest price from the provided orders.
     */
    static double getLowPrice(std::vector<OrderBookEntry> &orders);

    /**
     * @brief Inserts a new order into the order book.
     * 
     * This method adds a new order to the `orders` vector and then sorts the orders by timestamp.
     * 
     * @param order The new order to be inserted.
     */
    void insertOrder(OrderBookEntry &order);

    /**
     * @brief Matches ask orders with bid orders for a given product and timestamp.
     * 
     * This method attempts to match ask orders with bid orders for a specified product and timestamp.
     * It returns a vector of matched orders (sales) based on the available asks and bids.
     * 
     * @param product The product for which orders should be matched.
     * @param timestamp The timestamp to match orders at.
     * 
     * @return A vector of matched orders.
     */
    std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

private:
    /** A vector containing all the orders in the order book. */
    std::vector<OrderBookEntry> orders;
};

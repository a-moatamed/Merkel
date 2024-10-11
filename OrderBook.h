#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <math.h>
#include <algorithm>

class OrderBook
{
public:
    /** Constructor, reading a CSV data file*/
    OrderBook(std::string filename);

    /** return vector of all products inn the dataset*/
    std::vector<std::string> getKnownProducts();
    
    /** return vector of Orders according to the sent filters*/
    std::vector<OrderBookEntry> getOrders(OrderBookType type,
                                          std::string product,
                                          std::string timestamp);
    /** Return the earliest time in the orderbook*/
    std::string getEarliestTime();

    /** Return the next time after the sent time in the order book
     * if there is no next time stamp wrap around to the start
    */
    std::string getNextTime(std::string timestamp);

    static double getHeighPrice(std::vector<OrderBookEntry> &orders);
    static double getLowPrice(std::vector<OrderBookEntry> &orders);

    /**Function to calculate Mean of the price*/
    static double getMeanPrice(std::vector<OrderBookEntry> &orders);
    
    /**Function to calculate standard deviation*/
    static double getSDPrice(std::vector<OrderBookEntry> &orders);

    /**Function to insert user order*/
     void insertOrder(OrderBookEntry &order);

    std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

 private:
     std::vector<OrderBookEntry> orders;
};

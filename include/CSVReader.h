#pragma once
#include "OrderBookEntry.h"
#include <vector>
#include <string>

/**
 * @class CSVReader
 * @brief A utility class to read and parse CSV files into OrderBookEntry objects.
 */
class CSVReader
{
public:
    /**
     * @brief Default constructor for the CSVReader class.
     */
    CSVReader();

    /**
     * @brief Reads a CSV file and converts each line into OrderBookEntry objects.
     * @param csvFile The path to the CSV file to be read.
     * @return A vector of OrderBookEntry objects created from the CSV file.
     * @throws std::ios_base::failure if the file cannot be opened.
     */
    static std::vector<OrderBookEntry> readCSV(const std::string& csvFile);
    
    /**
     * @brief Converts the given strings to an OrderBookEntry object.
     * @param price The price of the order.
     * @param amount The amount of the order.
     * @param timestamp The timestamp of the order.
     * @param product The product for which the order is placed.
     * @param orderType The type of order (buy or sell).
     * @return The corresponding OrderBookEntry.
     * @throws std::invalid_argument if the price or amount is invalid.
     */
    static OrderBookEntry stringsToOBE(const std::string& price,
                                       const std::string& amount,
                                       const std::string& timestamp,
                                       const std::string& product,
                                       OrderBookType orderType); 

    /**
     * @brief Tokenizes a CSV line into individual strings based on a separator.
     * @param csvLine The line of CSV data.
     * @param separator The separator character, typically ',' for CSV.
     * @return A vector of strings, each representing a token.
     */
    static std::vector<std::string> tokenise(const std::string& csvLine, char separator);

private:
    /**
     * @brief Helper function to convert a vector of strings into an OrderBookEntry.
     * @param tokens A vector of strings representing the order data.
     * @return The corresponding OrderBookEntry object.
     * @throws std::invalid_argument if the number of tokens is incorrect.
     */
    static OrderBookEntry stringsToOBE(const std::vector<std::string>& tokens);
};

#include "CSVReader.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

CSVReader::CSVReader() {}


std::vector<OrderBookEntry> CSVReader::readCSV(const std::string& csvFilename)
{
    std::vector<OrderBookEntry> entries;
    std::ifstream csvFile(csvFilename);
    
    // Check if file opened successfully
    if (!csvFile.is_open())
    {
        throw std::ios_base::failure("Problem opening file: " + csvFilename);
    }

    std::string line;
    while (std::getline(csvFile, line))
    {
        try
        {
            // Tokenize line and convert to OrderBookEntry
            OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
            entries.push_back(obe);
           
        }
        catch (const std::exception& e)
        {
            // Log the error but continue processing other lines
            std::cerr << "Error parsing line - " << e.what() << std::endl;
        
        }
    }

    csvFile.close();
    std::cout << "CSVReader::readCSV successfully uploaded " << entries.size() << " entries." << std::endl;
    return entries;
}


std::vector<std::string> CSVReader::tokenise(const std::string& csvLine, char separator)
{
    std::vector<std::string> tokens;
    size_t start = csvLine.find_first_not_of(separator, 0);
    size_t end;

    while (start != std::string::npos)
    {
        end = csvLine.find_first_of(separator, start);
        tokens.push_back(csvLine.substr(start, end - start));
        start = csvLine.find_first_not_of(separator, end);
    }
    
    return tokens;
}


OrderBookEntry CSVReader::stringsToOBE(const std::vector<std::string>& tokens)
{
    if (tokens.size() != 5)
    {
        throw std::invalid_argument("Invalid number of tokens, expected 5.");
    }

    double price, amount;
    try
    {
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }
    catch (const std::exception& e)
    {
        throw std::invalid_argument("Invalid float values in tokens: " + tokens[3] + ", " + tokens[4]);
    }

    return OrderBookEntry{
        price,
        amount,
        tokens[0],  // Timestamp
        tokens[1],  // Product
        OrderBookEntry::stringToOrderBookType(tokens[2])  // Order Type
    };
}


OrderBookEntry CSVReader::stringsToOBE(const std::string& priceString,
                                       const std::string& amountString,
                                       const std::string& timestamp,
                                       const std::string& product,
                                       OrderBookType orderType)
{
    double price, amount;
    try
    {
        price = std::stod(priceString);
        amount = std::stod(amountString);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: Invalid float values for price: " << priceString << " or amount: " << amountString << std::endl;
        throw;
    }

    return OrderBookEntry{
        price,
        amount,
        timestamp,
        product,
        orderType
    };
}

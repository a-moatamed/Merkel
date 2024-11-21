#pragma once
#include <string>
#include <map>
#include <iostream>
#include "OrderBookEntry.h"
#include "CSVReader.h"

/**
 * @brief A class representing a wallet that holds various currencies.
 * 
 * The `Wallet` class allows inserting and removing currencies, checking if a certain amount of currency is present,
 * fulfilling orders from the order book, and processing sales that affect the wallet's contents.
 */
class Wallet
{
public:
    /**
     * @brief Default constructor for the Wallet class.
     * Initializes the wallet with an empty set of currencies.
     */
    Wallet();

    /**
     * @brief Inserts a certain amount of a given currency into the wallet.
     * 
     * @param type The type of the currency (e.g., "USD", "EUR").
     * @param amount The amount of the currency to insert.
     * 
     * @throws std::invalid_argument If the amount is negative.
     */
    void insertCurrency(const std::string& type, double amount);

    /**
     * @brief Removes a certain amount of a given currency from the wallet.
     * 
     * @param type The type of the currency (e.g., "USD", "EUR").
     * @param amount The amount of the currency to remove.
     * 
     * @return true If the removal is successful.
     * @return false If there is insufficient balance or if the currency doesn't exist.
     * 
     * @throws std::invalid_argument If the amount to remove is negative.
     */
    bool removeCurrency(const std::string& type, double amount);

    /**
     * @brief Checks if the wallet contains a sufficient amount of a given currency.
     * 
     * @param type The type of the currency (e.g., "USD", "EUR").
     * @param amount The required amount of the currency.
     * 
     * @return true If the wallet contains enough of the currency.
     * @return false If the wallet does not contain enough of the currency.
     */
    bool containsCurrency(const std::string& type, double amount);

    /**
     * @brief Checks if the wallet can fulfill an order from the order book.
     * 
     * @param order The `OrderBookEntry` representing the order.
     * 
     * @return true If the wallet has sufficient funds to fulfill the order.
     * @return false If the wallet cannot fulfill the order.
     */
    bool canFulfillOrder(const OrderBookEntry& order);

    /**
     * @brief Processes a sale that affects the wallet contents (either a bid sale or an ask sale).
     * 
     * @param sale The `OrderBookEntry` representing the sale.
     */
    void processSale(OrderBookEntry& sale);

    /**
     * @brief Converts the wallet's contents to a string format.
     * 
     * @return A string representation of the wallet's contents.
     */
    std::string toString() const;

private:
    // A map to store currency types and their corresponding balances.
    std::map<std::string, double> currencies;
};


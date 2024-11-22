#include "Wallet.h"
#include <stdexcept> // For std::invalid_argument

Wallet::Wallet() {
    // Constructor with no initial content, the wallet starts empty.
}

void Wallet::insertCurrency(const std::string& type, double amount)
{
    if (amount < 0)
    {
        throw std::invalid_argument("Cannot insert a negative amount of currency.");
    }

    // If the currency doesn't exist in the wallet, initialize it with zero balance.
    if (currencies.count(type) == 0)
    {
        currencies[type] = 0;
    }

    currencies[type] += amount; // Add the specified amount to the currency balance.
}

bool Wallet::removeCurrency(const std::string& type, double amount)
{
    if (amount < 0)
    {
        throw std::invalid_argument("Cannot remove a negative amount of currency.");
    }

    // Check if the currency exists in the wallet.
    if (currencies.count(type) == 0)
    {
        std::cout << "No currency available for " << type << std::endl;
        return false; // Currency not found in wallet.
    }

    // Check if there is enough currency to remove.
    if (containsCurrency(type, amount))
    {
        currencies[type] -= amount;
        return true; // Successfully removed the currency.
    }
    else
    {
        std::cout << "Not enough balance to remove." << std::endl;
        return false; // Not enough funds.
    }
}

bool Wallet::containsCurrency(const std::string& type, double amount)
{
    return currencies.count(type) > 0 && currencies[type] >= amount;
}

std::string Wallet::toString() const
{
    std::string result;
    for (const auto& pair : currencies)
    {
        result += pair.first + " : " + std::to_string(pair.second) + "\n";
    }
    return result;
}

bool Wallet::canFulfillOrder(const OrderBookEntry& order)
{
    std::vector<std::string> currs = CSVReader::tokenise(order.product, '/');
    double requiredAmount = 0.0; // Initialize the variable
    std::string currency;

    // Check for ask order type
    if (order.orderType == OrderBookType::ask)
    {
        requiredAmount = order.amount;
        currency = currs[0];
    }
    // Check for bid order type
    else if (order.orderType == OrderBookType::bid)
    {
        currency = currs[1];
        requiredAmount = order.amount * order.price;
    }

    // Ensure we have enough of the currency
    return containsCurrency(currency, requiredAmount);
}

void Wallet::processSale(OrderBookEntry& sale)
{
    std::vector<std::string> currs = CSVReader::tokenise(sale.product, '/');

    if (sale.orderType == OrderBookType::asksale)
    {
        double outgoingAmount = sale.amount;
        std::string outgoingCurrency = currs[0];
        double incomingAmount = sale.amount * sale.price;
        std::string incomingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
    else if (sale.orderType == OrderBookType::bidsale)
    {
        double incomingAmount = sale.amount;
        std::string incomingCurrency = currs[0];
        double outgoingAmount = sale.amount * sale.price;
        std::string outgoingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
}

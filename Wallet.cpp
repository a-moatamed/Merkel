#include "Wallet.h"


Wallet::Wallet()
{
}

void Wallet::insertCurrency(std::string type, double amount)
{
    double balance;
    // check if the amount is a negative number
    if (amount < 0)
    {
        throw std::exception{};
    }
    // initializing this currency if it isn't exist in the wallet after checking 
    if (currencies.count(type) == 0)
    {
        balance = 0;
    }
    else
    {
        balance = currencies[type];
    }
    balance += amount;
    currencies[type] = balance;
}

bool Wallet::removeCurrency(std::string type, double amount) 
{
    double balance;
    // check if the amount wanted to remove is a negative(it's adding)
    if (amount < 0)
    {
        throw std::exception{};
    }
    // check if the currency is already exist
    if (currencies.count(type) == 0)
    {
        std::cout << "No currency here for " << type << std::endl;
        return false; // nothing in the wallet
    }
    else
    {
        if (containsCurrency(type, amount)) // we have enough
        {
            // std::cout << "Removing .." << type << " : " << amount << std::endl;
            currencies[type] -= amount;
            return true;
        }
        else // they have it but not enough
            {
                std::cout << "Not enough balance to remove." << std::endl;
                return false;
            }
    }
    balance += amount;
    currencies[type] = balance;
}

bool Wallet::containsCurrency(std::string type, double amount)
{
    if (currencies.count(type) == 0)
        return false;
    else
        return currencies[type] >= amount;

    return false;
}

std::string Wallet::toString()
{
    std::string s;
    for (std::pair<std::string, double> pair : currencies)
    {
        std::string currency = pair.first;
        double amount = pair.second;
        s += currency + " : " + std::to_string(amount) + "\n";
    }

    return s;
}







bool Wallet::canFulfillOrder(OrderBookEntry order)
{
    // vector contains the 2 product curruncies
    std::vector<std::string> currs = CSVReader::tokenise(order.product, '/');
    double amount;
    std::string currency;
    //ask
    if (order.orderType == OrderBookType::ask)
    {
        amount = order.amount;
        currency = currs[0];
    }
    if (order.orderType == OrderBookType::bid)
    {
        currency = currs[1];
        amount = order.amount * order.price;
    }
    return containsCurrency(currency, amount);

    return false;
}

void Wallet::processSale(OrderBookEntry &sale)
{
    // vector contains the 2 product curruncies
    std::vector<std::string> currs = CSVReader::tokenise(sale.product, '/');

    //ask
    if (sale.orderType == OrderBookType::asksale)
    {
        double outGoingAmount = sale.amount;
        std::string outGoingCurrency = currs[0];
        double inComingAmount = sale.amount * sale.price;
        std::string inComingCurrency = currs[1];

        //update the wallet currencies content
        currencies[inComingCurrency] += inComingAmount;
        currencies[outGoingCurrency] -= outGoingAmount;
    }

    //bid
    if (sale.orderType == OrderBookType::bidsale)
    {
        double inComingAmount = sale.amount;
        std::string inComingCurrency = currs[0];
        double outGoingAmount = sale.amount * sale.price;
        std::string outGoingCurrency = currs[1];

        //update the wallet currencies content
        currencies[inComingCurrency] += inComingAmount;
        currencies[outGoingCurrency] -= outGoingAmount;
    }
   

}

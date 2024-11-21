#include <string>
#include <map>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <iostream>
class Wallet
{
    public:
        Wallet();
        /** insert currency to the wallet */
        void insertCurrency(std::string type, double amount);

        /** remove currency from the wallet */
        bool removeCurrency(std::string type, double amount);

        /** check if there is enough amount from this currency */
        bool containsCurrency(std::string type, double amount);

        /** check if the wallet can cope the order from orderbook entry */
        bool canFulfillOrder(OrderBookEntry order);

        /** update the content of the wallet according to the owner order */
        void processSale(OrderBookEntry &sale);

        /** print the Wallet's contents in string format */
        std::string toString();

    private:
        std::map<std::string, double> currencies; 
};
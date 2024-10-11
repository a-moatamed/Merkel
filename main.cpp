#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include "CSVReader.h"
#include "OrderBook.h"


// prototypes of all functions
// double computeAveragePrice(std::vector<OrderBookEntry> &entries); 
// double computeLowPrice(std::vector<OrderBookEntry> &entries);
// double computeHighPrice(std::vector<OrderBookEntry> &entries);
// double computePriceSpread(std::vector<OrderBookEntry> &entries); 

int main()
{

    MerkelMain app{};
    app.init();

    // Wallet myWallet{};
    // std::cout << "Inserting 10 BTC" << std::endl;
    // myWallet.insertCurrency("BTC", 10);
    // std::cout << "Wallet contents "<<std::endl << myWallet.toString() << std::endl;

    // // std::cout << "Inserting 10 ETH" << std::endl;
    // myWallet.insertCurrency("ETH", 10);
    // std::cout << "Wallet contents "<<std::endl << myWallet.toString() << std::endl;

    // std::cout << "Inserting 10 ETH" << std::endl;
    // myWallet.insertCurrency("ETH", 10);
    // std::cout << "Wallet contents "<<std::endl << myWallet.toString() << std::endl;

    // std::cout << "Inserting -10 ETH" << std::endl;
    // myWallet.insertCurrency("ETH", -10);
    // std::cout << "Wallet contents "<<std::endl << myWallet.toString() << std::endl;






    // std::cout << "Removing 5 BTC" << std::endl;
    // myWallet.removeCurrency("BTC", 5);
    // std::cout << "Wallet contents "<<std::endl << myWallet.toString() << std::endl;

    // std::cout << "Removing 10 BTC" << std::endl;
    // myWallet.removeCurrency("BTC", 10);
    // std::cout << "Wallet contents "<<std::endl << myWallet.toString() << std::endl;

    // // std::cout << "Removing -10 BTC" << std::endl;
    // myWallet.removeCurrency("BTC", -10);
    // std::cout << "Wallet contents "<<std::endl << myWallet.toString() << std::endl;









    
    // std::vector<OrderBookEntry> test_orders;
    // CSVReader reader;

    // OrderBookEntry obe = reader.stringsToOBE(reader.tokenise(
    //     "2020/03/17 17:01:24.884492,ETH/BTC,bid,0.02187308,7.44564869", ','));
    // test_orders.push_back(obe);

    // obe = reader.stringsToOBE(reader.tokenise(
    //     "2020/03/17 17:01:24.884492,ETH/BTC,bid,0.02187307,3.467434", ','));
    // test_orders.push_back(obe);

    // obe = reader.stringsToOBE(reader.tokenise(
    //     "2020/03/17 17:01:24.884492,ETH/BTC,bid,0.02187305,6.85567013", ','));
    // test_orders.push_back(obe);


    // std::cout << "Mean is: " << OrderBook::getMeanPrice(test_orders)<<std::endl;
    // std::cout << "SD is: " << OrderBook::getSDPrice(test_orders)<<std::endl;

    return 0;
}

// double computeAveragePrice(std::vector<OrderBookEntry> &entries)
// {

//     double sum = 0;
//     for(auto e: entries)
//     {
//         sum += e.price;
//     }
//     return sum / entries.size();
// }
// double computeLowPrice(std::vector<OrderBookEntry> &entries)
// {
//     double low = entries[0].price;
//     for (int i = 1; i < entries.size(); ++i)
//     {
//         if (entries[i].price < low)
//             low = entries[i].price;
//     }
//     return low;
// }
// double computeHighPrice(std::vector<OrderBookEntry> &entries)
// {
//     double high = entries[0].price;
//     for (int i = 1; i < entries.size(); ++i)
//     {
//         if (entries[i].price > high)
//             high = entries[i].price;
//     }
//     return high;
// }
// double computePriceSpread(std::vector<OrderBookEntry> &entries)
// {
//     return 0;
// }

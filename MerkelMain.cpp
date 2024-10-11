#include "MerkelMain.h"


MerkelMain::MerkelMain()
{
}

void MerkelMain::init()
{

    int input;
    currentTime = orderBook.getEarliestTime();
    wallet.insertCurrency("BTC", 10);
    while (true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}
int MerkelMain::getUserOption()
{

    int userOption = 0;
    std::string line;
    std::cout << "Type in 1-6: ";
    std::getline(std::cin, line);

    try
    {
        userOption = std::stoi(line);
    }
    catch (const std::exception &e)
    {
    }

    std::cout << "Your choice is: " << userOption << std::endl;

    if (userOption > 6 || userOption < 1)
    {
        std::cout << "Please Enter a valid option.." << std::endl;
        std::cout << std::endl;
        return 6;
    }

    return userOption;
}

void MerkelMain::help()
{

    std::cout << std::endl;
    std::cout << "Help - choose options from the menu" << std::endl;
    std::cout << "and follow the on-screen instructions." << std::endl;
}

void MerkelMain::printMarketStats()
{

    for (std::string const &p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        std::cout << "Askes for product: " << entries.size() << std::endl;
        std::cout << "Max Ask price is: " << OrderBook::getHeighPrice(entries) << std::endl;
        std::cout << "Min Ask price is: " << OrderBook::getLowPrice(entries) << std::endl;
        std::cout << "Mean of Ask price is: " << OrderBook::getMeanPrice(entries) << std::endl;
        std::cout << "standard Deviation of Ask price is: " << OrderBook::getSDPrice(entries) << std::endl;
        std::cout << std::endl;
    }

    
}

void MerkelMain::enterAsk()
{
    std::cout << std::endl;
    std::cout << "Make an ask - enter the amount: product,price, amount, eg ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::cout << "Your input is: " << input << std::endl;
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');

    if (tokens.size() != 3)
        std::cout << "Bad Input string!! " << std::endl;
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::ask);
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet is good." << std::endl;
                orderBook.insertOrder(obe);
                std::cout << "Added one OrderBook to orders." << std::endl;
            }
            else
                std::cout<< "Wallet has insufficient funds." << std::endl;
            // std::cout << obe.amount << ',' << obe.price << ',' << obe.product << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cout << "MerkelMain::enterAsk Bad input!" << std::endl;
        }
    }
}

void MerkelMain::enterBid()
{
    std::cout << std::endl;
    std::cout << "Make a bid - enter the amount: product,price, amount, eg ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::cout << "Your input is: " << input << std::endl;
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');

    if (tokens.size() != 3)
        std::cout << "Bad Input string!! " << std::endl;
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::bid);
            obe.username = "simuser";

            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet is good." << std::endl;
                orderBook.insertOrder(obe);
                std::cout << "Added one OrderBook to orders." << std::endl;
            }
            else
                std::cout<< "Wallet has insufficient funds." << std::endl;
            // std::cout << obe.amount << ',' << obe.price << ',' << obe.product << std::endl;
        
            std::cout << obe.amount << ',' << obe.price << ',' << obe.product << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cout << "MerkelMain::enterBid Bad input!" << std::endl;
        }

        
    }
}

void MerkelMain::printWallet()
{
    std::cout << std::endl;
    std::cout << "Your wallet is ......" << std::endl;
    std::cout << wallet.toString() << std::endl;
}

void MerkelMain::gotoNextTimeframe()
{
    std::cout << std::endl;
    std::cout << "Going to next time frame .. " << std::endl;
    for (std::string &p : orderBook.getKnownProducts())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry &sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
            if(sale.username == "simuser")
            {
                // update the wallet
                wallet.processSale(sale);
            }
        }
    }
    currentTime = orderBook.getNextTime(currentTime);
}

void MerkelMain::printMenu()

{
    // print the minue
    std::cout << std::endl
              << "**********************************" << std::endl
              << std::endl;
    std::cout << "1: Print help" << std::endl;
    std::cout << "2: Print exchange stats" << std::endl;
    std::cout << "3: Place an ask" << std::endl;
    std::cout << "4: Place a bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6: Continue" << std::endl;
    std::cout << "=============================" << std::endl;

    std::cout << "Current Time is: " << currentTime << std::endl
              << std::endl;
    std::cout << std::endl;
}

void MerkelMain::processUserOption(int userOption)
{
    // creating a data structure contain menu

    // map from int to function pointers
    std::map<int, void (MerkelMain::*)()> menu;
    menu[1] = &MerkelMain::help;
    menu[2] = &MerkelMain::printMarketStats;
    menu[3] = &MerkelMain::enterAsk;
    menu[4] = &MerkelMain::enterBid;
    menu[5] = &MerkelMain::printWallet;
    menu[6] = &MerkelMain::gotoNextTimeframe;

    (this->*menu[userOption])();
}

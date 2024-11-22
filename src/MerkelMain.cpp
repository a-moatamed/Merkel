#include "MerkelMain.h"

// Constructor: Initializes any necessary objects and sets default values
MerkelMain::MerkelMain()
{
}

// Initializes the main loop of the program, handles user interaction
void MerkelMain::init()
{
    int input;
    currentTime = orderBook.getEarliestTime();  // Get the earliest time from the order book
    wallet.insertCurrency("BTC", 10);  // Insert 10 BTC into the wallet at the beginning

    // Main loop: Keeps running until the user chooses to exit
    while (true)
    {
        printMenu();  // Display the menu options
        input = getUserOption();  // Get user input
        processUserOption(input);  // Process the chosen option
    }
}

// Gets the option selected by the user from the menu
int MerkelMain::getUserOption()
{
    int userOption = 0;
    std::string line;
    std::cout << "Type in 1-6: ";  // Prompt user to choose an option
    std::getline(std::cin, line);

    // Try to convert the input string to an integer
    try
    {
        userOption = std::stoi(line);
    }
    catch (const std::exception &e)
    {
        // Handle invalid input gracefully (no crash)
    }

    // Validate the user input and ensure it's within the valid range
    if (userOption > 6 || userOption < 1)
    {
        std::cout << "Please Enter a valid option.." << std::endl;
        std::cout << std::endl;
        return 6;  // Return 6 if the option is invalid (so the loop can proceed)
    }

    return userOption;
}

// Displays help instructions for the user
void MerkelMain::help()
{
    std::cout << std::endl;
    std::cout << "Help - choose options from the menu" << std::endl;
    std::cout << "and follow the on-screen instructions." << std::endl;
    std::cout << std::endl;
}

// Prints market stats for each known product in the order book
void MerkelMain::printMarketStats()
{
    // Iterate through all known products
    for (const std::string &p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        std::cout << "Asks for product: " << entries.size() << std::endl;
        std::cout << "Max Ask price is: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min Ask price is: " << OrderBook::getLowPrice(entries) << std::endl;
        std::cout << std::endl;
    }
}

// Allows the user to enter an ask order
void MerkelMain::enterAsk()
{
    std::cout << std::endl;
    std::cout << "Make an ask - enter the amount: product,price, amount, eg ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);  // Get user input for ask
    
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');  // Tokenize the input
    
    if (tokens.size() != 3)  // Ensure that the input has the correct number of tokens
    {
        std::cout << "Invalid Input!! " << std::endl;
        std::cout << std::endl;
    }
    else
    {
        try
        {
            // Convert the tokens into an OrderBookEntry and process the ask order
            OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::ask);
            obe.username = "simuser";  // Assign a username to the order
            if (wallet.canFulfillOrder(obe))  // Check if the wallet has enough funds
            {
                orderBook.insertOrder(obe);  // Insert the order into the order book
                std::cout << "Added one OrderBook to orders." << std::endl;
            }
            else
                std::cout << "Wallet has insufficient funds." << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cout << "Invalid Input!" << std::endl;
        }
    }
}

// Allows the user to enter a bid order (similar to enterAsk)
void MerkelMain::enterBid()
{
    std::cout << std::endl;
    std::cout << "Make a bid - enter the amount: product,price, amount, eg ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);  // Get user input for bid
    
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');  // Tokenize the input

    if (tokens.size() != 3)
        std::cout << "Invalid Input !! " << std::endl;
    else
    {
        try
        {
            // Convert the tokens into an OrderBookEntry and process the bid order
            OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::bid);
            obe.username = "simuser";

            if (wallet.canFulfillOrder(obe))  // Check if the wallet can fulfill the bid order
            {
                orderBook.insertOrder(obe);  // Insert the order into the order book
                std::cout << "Added one OrderBook to orders." << std::endl;
            }
            else
                std::cout << "Wallet has insufficient funds." << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cout << "Invalid Input!" << std::endl;
        }
    }
}

// Prints the user's wallet details
void MerkelMain::printWallet()
{
    std::cout << std::endl;
    std::cout << "Your wallet contains: " << std::endl;
    std::cout << wallet.toString() << std::endl;
}

// Advances to the next timeframe and processes sales
void MerkelMain::gotoNextTimeframe()
{
    std::cout << std::endl;
    std::cout << "Going to next time frame .. " << std::endl;
    std::cout << std::endl;
    // Process sales for each product in the order book
    for (std::string &product : orderBook.getKnownProducts())
    {
        
        std::cout << "matching " << product << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(product, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        std::cout << std::endl;
        for (OrderBookEntry &sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
            if(sale.username == "simuser")  // Update the wallet if the sale was made by the user
            {
                wallet.processSale(sale);
            }
        }
    }
    currentTime = orderBook.getNextTime(currentTime);  // Get the next timeframe
}

// Displays the main menu with available options
void MerkelMain::printMenu()
{
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
    std::cout<<std::endl;

    std::cout << "Current Time is: " << currentTime << std::endl
              << std::endl;
}

// Processes the user's selected option from the menu
void MerkelMain::processUserOption(int userOption)
{
    // Map of options to corresponding member functions
    std::map<int, void (MerkelMain::*)()> menu;
    menu[1] = &MerkelMain::help;
    menu[2] = &MerkelMain::printMarketStats;
    menu[3] = &MerkelMain::enterAsk;
    menu[4] = &MerkelMain::enterBid;
    menu[5] = &MerkelMain::printWallet;
    menu[6] = &MerkelMain::gotoNextTimeframe;

    // Call the corresponding function based on the selected option
    (this->*menu[userOption])();
}

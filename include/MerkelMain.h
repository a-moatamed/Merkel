#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include <iostream>
#include <limits>
#include <map> 
#include "CSVReader.h"
#include "Wallet.h"

/** 
 * @class MerkelMain
 * @brief Represents the main logic and user interface for the Merkel application.
 * 
 * The class manages the main loop of the application, handles user interactions via menus,
 * processes bids and asks, and manages the order book and wallet.
 */
class MerkelMain
{
public:
    /** 
     * @brief Constructor to initialize the MerkelMain instance. 
     * Initializes the order book with data from a CSV file and sets up the wallet.
     */
    MerkelMain();

    /** 
     * @brief Initializes the main loop of the program. 
     * Handles user interaction, prints the menu, gets user options, and processes them in a loop.
     * This loop will continue to run until the user exits the program.
     */
    void init();

private:
    /** 
     * @brief Prints the main menu with available options to the user. 
     * Displays the current time and prompts the user to select an option from the menu.
     */
    void printMenu();

    /** 
     * @brief Displays help instructions for the user. 
     * Provides guidance on how to navigate the menu and interact with the system.
     */
    void help();

    /** 
     * @brief Prints statistics about the market for each known product in the order book. 
     * Shows the number of asks for each product, as well as the highest and lowest ask prices.
     */
    void printMarketStats();

    /** 
     * @brief Allows the user to enter an ask order (a sell order). 
     * The user inputs the product, price, and amount. The order is processed if 
     * the wallet has sufficient funds.
     */
    void enterAsk();

    /** 
     * @brief Allows the user to enter a bid order (a buy order). 
     * The user inputs the product, price, and amount. The order is processed if the 
     * wallet has sufficient funds.
     */
    void enterBid();

    /** 
     * @brief Prints the user's wallet details. 
     * Displays the available balance and owned currencies in the user's wallet.
     */
    void printWallet();

    /** 
     * @brief Advances to the next timeframe in the order book and processes any sales. 
     * This method matches asks and bids in the order book, processes sales, 
     * and updates the wallet with any successful transactions.
     */
    void gotoNextTimeframe();

    /** 
     * @brief Prompts the user to select an option from the menu. 
     * The function validates the input and returns the corresponding menu option. 
     * If the input is invalid, option 6 is returned. 
     * @return The user's selected option (an integer between 1 and 6).
     */
    int getUserOption();

    /** 
     * @brief Processes the selected option from the user. 
     * Executes the corresponding function based on the user's menu choice. This is done 
     * through a mapping of option numbers to functions. 
     * @param userOption The selected menu option (integer).
     */
    void processUserOption(int userOption);

    /** 
     * @brief A string representing the current time.
     * This is updated as the program progresses to simulate the passage of time in the 
     * trading system.
     */
    std::string currentTime;

    /** 
     * @brief The order book instance used to manage orders. 
     * It is initialized with data from a CSV file and handles the insertion and 
     * retrieval of orders.
     */
    OrderBook orderBook{"20200317.csv"};

    /** 
     * @brief The wallet instance representing the user's available funds and currency holdings. 
     * The wallet allows the user to check their balance, add funds, and check if they 
     * can fulfill orders.
     */
    Wallet wallet;
};

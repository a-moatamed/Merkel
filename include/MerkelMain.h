#pragma once
#include<vector>
#include"OrderBookEntry.h"
#include "OrderBook.h"
#include <iostream>
#include <limits>
#include <map> 
#include "CSVReader.h"
#include "Wallet.h"

class MerkelMain
{
    public:
        MerkelMain();
        void init();
    private:
        // functions used for main menu 
        void printMenu();
        void help();
        void printMarketStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeframe();
        int getUserOption();
        void processUserOption(int userOption);
        std::string currentTime;

        OrderBook orderBook{"20200317.csv"};

        Wallet wallet;
};
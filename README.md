# Merkel Trading System

## Overview
The Merkel Trading System is a simple yet powerful application designed to simulate a cryptocurrency or asset trading environment. Users can interact with a virtual order book to place bid and ask orders, view market statistics, and manage their wallet balance. The system processes orders, matches bids and asks, and updates the wallet accordingly.

Built using C++, this project includes an order-matching engine, wallet management, CSV-based order book loading, and a command-line interface for user interaction.

---

## Features

### Order Book Management
- Support for two main types of orders: **Bid (buy)** and **Ask (sell)**.
- Order insertion, filtering, matching, and market statistics reporting.

### Wallet Management
- Track funds and manage multiple currencies.
- Verify if sufficient funds are available to fulfill orders.

### CSV Integration
- Load orders from a CSV file.
- Convert CSV data into order entries for processing.

### User Interface
An interactive console interface with options to:
- Place orders (bids/asks).
- View market statistics.
- Manage wallet balances.
- Process matched orders.
- Access help and instructions.

---

## Requirements
- **C++ Compiler**: C++11 compatible (e.g., `g++`).
- **CMake** (optional): For easier build management.

---

## Setup & Installation

### Clone the repository:
```bash
git clone https://github.com/a-moatamed/trade-platform.git
cd trade-platform
```
# Build and Run the Project

## Build the Project

If a `Makefile` is available in the project directory, you can build the project with a single command:

```bash
make
```
# Run the Application

After building the project, you can run the application using the following command:

```bash
./bin/my_program
```

# Application Structure

## Directories and Files

- **`src/`**: Contains source code files for core functionality.
  - **`main.cpp`**: Application entry point.
  - **`MerkelMain.cpp`**: Implements core logic, user interaction, and main loop.
  - **`OrderBook.cpp`**: Manages the order book (insertion, matching, filtering).
  - **`Wallet.cpp`**: Handles wallet operations (balances, order fulfillment).
  - **`CSVReader.cpp`**: Reads and parses CSV files into order entries.

- **`include/`**: Header files for the classes in `src/`.
  - **`MerkelMain.h`**: Declares the core application class.
  - **`OrderBook.h`**: Manages orders and processing.
  - **`OrderBookEntry.h`**: Defines an order's structure.
  - **`CSVReader.h`**: Utilities for reading CSV files.
  - **`Wallet.h`**: Manages user funds and transactions.

- **`obj/`**: Object files generated during build.

- **`bin/`**: Final executable file.

- **`20200317.csv`**: Example CSV file containing sample order book data (optional for initialization).

---

## Class Descriptions

### `MerkelMain`
- Orchestrates user interactions, core logic, and the main loop.

#### Key Methods:
- **`init()`**: Starts the application.
- **`printMenu()`**: Displays the menu options.
- **`enterAsk()` / `enterBid()`**: Place ask or bid orders.
- **`gotoNextTimeframe()`**: Processes orders and advances time.
- **`printWallet()`**: Displays wallet balances.

### `OrderBook`
- Manages the list of orders and matches bid/ask orders.
- Reads order data from CSV and provides market statistics.

#### Key Methods:
- **`getOrders()`**: Filters orders by criteria.
- **`insertOrder()`**: Adds a new order.
- **`matchAsksToBids()`**: Matches ask orders with bid orders.
- **`getHighPrice()` / `getLowPrice()`**: Retrieve price statistics.

### `OrderBookEntry`
- Represents an order with price, amount, timestamp, and product.

#### Key Methods:
- **`stringToOrderBookType()`**: Converts strings to order types.
- **Comparison Methods**: For sorting by timestamp or price.

### `CSVReader`
- Reads and converts CSV files into order entries.

#### Key Methods:
- **`readCSV()`**: Reads CSV file contents.
- **`stringsToOBE()`**: Parses CSV strings into `OrderBookEntry` objects.
- **`tokenise()`**: Splits a line into tokens.

### `Wallet`
- Tracks user funds and verifies order fulfillment.

#### Key Methods:
- **`canFulfillOrder()`**: Checks if an order can be fulfilled.
- **`containsCurrency()`**: Verifies if a specific currency is available.

---

## Usage

After starting the program, you will be presented with the following menu options:

1. **View Market Stats**: See the number of asks, highest, and lowest ask prices.
2. **Enter Ask Order**: Specify product, price, and amount to sell.
3. **Enter Bid Order**: Specify product, price, and amount to buy.
4. **View Wallet**: Check wallet balances.
5. **Go to Next Timeframe**: Process orders and advance time.
6. **Help**: Display help instructions.

### Example Interaction
```plaintext
1. Help
2. View Market Stats
3. Enter Ask Order
4. Enter Bid Order
5. View Wallet
6. Go to Next Timeframe

Choose an option: 1
```

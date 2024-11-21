#pragma once

#include <string>
#include <stdexcept>  // For exceptions

/**
 * @brief Enumeration representing the type of an order in the order book.
 * 
 * This enum class defines different types of orders that could exist in an order book, including:
 * - `bid`: A buy order.
 * - `ask`: A sell order.
 * - `unkown`: Unknown or invalid order type.
 * - `asksale`: A sale of an ask order (e.g., when the ask is matched).
 * - `bidsale`: A sale of a bid order (e.g., when the bid is matched).
 */
enum class OrderBookType {
    bid,       /**< A buy order. */
    ask,       /**< A sell order. */
    unkown,    /**< Invalid or unrecognized order type. */
    asksale,   /**< A sale of an ask order. */
    bidsale    /**< A sale of a bid order. */
};

/**
 * @brief Represents an entry in the order book.
 * 
 * This class stores information about a specific order in the order book, including:
 * - Price of the order.
 * - Amount of the order.
 * - Timestamp when the order was placed.
 * - The product associated with the order.
 * - The type of the order (bid, ask, etc.).
 * - The username of the user who placed the order.
 */
class OrderBookEntry {
public:
    /**
     * @brief Constructs an OrderBookEntry object.
     * 
     * Initializes an order book entry with price, amount, timestamp, product, order type, and an optional username.
     * If no username is provided, "dataset" is used by default.
     * 
     * @param _price The price of the order.
     * @param _amount The amount of the order.
     * @param _timestamp The timestamp when the order was placed.
     * @param _product The product associated with the order.
     * @param _orderType The type of the order (bid, ask, etc.).
     * @param _username The username of the person who placed the order (defaults to "dataset").
     */
    OrderBookEntry(
        double _price,
        double _amount,
        std::string _timestamp,
        std::string _product,
        OrderBookType _orderType,
        std::string _username = "dataset"
    );

    /**
     * @brief Converts a string to an OrderBookType enum.
     * 
     * This static method converts a string (e.g., "ask", "bid") into the corresponding
     * `OrderBookType` enum. If the string does not match a known type, it returns `OrderBookType::unkown`.
     * 
     * @param s The string representing the order type.
     * @return The corresponding `OrderBookType` enum.
     * @throws std::invalid_argument If the string is not recognized.
     */
    static OrderBookType stringToOrderBookType(const std::string& s);

    /**
     * @brief Compares two `OrderBookEntry` objects by timestamp.
     * 
     * This static method compares two entries based on their timestamp (in ascending order).
     * 
     * @param e1 The first order book entry.
     * @param e2 The second order book entry.
     * @return `true` if `e1.timestamp` is less than `e2.timestamp`; otherwise, `false`.
     */
    static bool compareByTimestamp(const OrderBookEntry& e1, const OrderBookEntry& e2);

    /**
     * @brief Compares two `OrderBookEntry` objects by price in ascending order.
     * 
     * This static method compares two entries based on their price in ascending order.
     * 
     * @param e1 The first order book entry.
     * @param e2 The second order book entry.
     * @return `true` if `e1.price` is less than `e2.price`; otherwise, `false`.
     */
    static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2);

    /**
     * @brief Compares two `OrderBookEntry` objects by price in descending order.
     * 
     * This static method compares two entries based on their price in descending order.
     * 
     * @param e1 The first order book entry.
     * @param e2 The second order book entry.
     * @return `true` if `e1.price` is greater than `e2.price`; otherwise, `false`.
     */
    static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2);

    double price;          /**< The price of the order. */
    double amount;         /**< The amount of the order. */
    std::string timestamp; /**< The timestamp when the order was placed. */
    std::string product;   /**< The product associated with the order. */
    OrderBookType orderType; /**< The type of the order (bid, ask, etc.). */
    std::string username;  /**< The username of the person who placed the order. */
};

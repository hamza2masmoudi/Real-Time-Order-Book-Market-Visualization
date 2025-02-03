#pragma once
#include <map>
#include <mutex>
#include <vector>
#include <cstdint>
#include <functional>

enum class OrderType { LIMIT, MARKET };

struct Order {
    uint64_t id;
    double price;
    double quantity;
    bool is_bid;  // true = buy, false = sell
    OrderType type;
    uint64_t timestamp;
};

class OrderBook {
public:
    struct Trade {
        double price;
        double quantity;
        uint64_t taker_order_id;
        uint64_t maker_order_id;
    };

    void add_order(const Order& order);
    void cancel_order(uint64_t order_id);
    const std::map<double, double, std::greater<double>>& get_bids() const;
    const std::map<double, double>& get_asks() const;
    std::vector<Trade> get_trades();

private:
    std::map<double, double, std::greater<double>> bids;
    std::map<double, double> asks;
    std::vector<Trade> trades;
    mutable std::mutex mtx;
};
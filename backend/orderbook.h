#pragma once

#include <map>
#include <mutex>
#include <vector>
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <chrono>

enum class OrderType { LIMIT, MARKET };

struct Order {
    uint64_t id;
    double price;
    double quantity;
    bool is_bid;
    OrderType type;
    uint64_t timestamp;
    std::chrono::steady_clock::time_point submit_time;
};

class OrderBook {
public:
    struct Trade {
        uint64_t timestamp;  // Fix: Ensure timestamp exists
        double price;
        double quantity;
        uint64_t taker_order_id;
        uint64_t maker_order_id;
    };

    double match_order(const Order& order);
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
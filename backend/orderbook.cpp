#include "orderbook.h"

void OrderBook::add_order(const Order& order) {
    std::lock_guard<std::mutex> lock(mtx);
    if (order.is_bid) {
        bids[order.price] += order.quantity;
    } else {
        asks[order.price] += order.quantity;
    }
}

void OrderBook::cancel_order(uint64_t order_id) {
    // For simplicity, not implemented.
}

const std::map<double, double, std::greater<double>>& OrderBook::get_bids() const {
    return bids;
}

const std::map<double, double>& OrderBook::get_asks() const {
    return asks;
}

std::vector<OrderBook::Trade> OrderBook::get_trades() {
    std::lock_guard<std::mutex> lock(mtx);
    auto copy = trades;
    trades.clear();
    return copy;
}
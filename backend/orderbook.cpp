#include "orderbook.h"

void OrderBook::add_order(const Order& order) {
    std::lock_guard<std::mutex> lock(mtx);
    // Round price to 2 decimals for aggregation.
    double roundedPrice = std::round(order.price * 100.0) / 100.0;
    if (order.is_bid) {
        bids[roundedPrice] += order.quantity;
    } else {
        asks[roundedPrice] += order.quantity;
    }
}

void OrderBook::cancel_order(uint64_t /*order_id*/) {
    // Not implemented in this demo.
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

double OrderBook::match_order(const Order& order) {
    // This function attempts to match the incoming order.
    // For a buy order, match with the ask side;
    // for a sell order, match with the bid side.
    std::lock_guard<std::mutex> lock(mtx);
    double tradedVolume = 0.0;
    if (order.is_bid) {
        // Buy order: iterate through asks (lowest ask first)
        while (!asks.empty() && tradedVolume < order.quantity) {
            double askPrice = asks.begin()->first;
            // For LIMIT orders, only match if order.price >= askPrice.
            if (order.type == OrderType::LIMIT && order.price < askPrice)
                break;
            auto it = asks.begin();
            double available = it->second;
            double volume = std::min(order.quantity - tradedVolume, available);
            tradedVolume += volume;
            it->second -= volume;
            // Record a trade (using askPrice as execution price)
            Trade trade;
            trade.timestamp = order.timestamp; // use order's timestamp for simplicity
            trade.price = it->first;  // price level
            trade.quantity = volume;
            trade.taker_order_id = order.id;
            trade.maker_order_id = 0;  // Dummy value (aggregated order)
            trades.push_back(trade);
            if (it->second <= 0)
                asks.erase(it);
        }
    } else {
        // Sell order: iterate through bids (highest bid first)
        while (!bids.empty() && tradedVolume < order.quantity) {
            double bidPrice = bids.begin()->first;
            if (order.type == OrderType::LIMIT && order.price > bidPrice)
                break;
            auto it = bids.begin();
            double available = it->second;
            double volume = std::min(order.quantity - tradedVolume, available);
            tradedVolume += volume;
            it->second -= volume;
            Trade trade;
            trade.timestamp = order.timestamp;
            trade.price = it->first;
            trade.quantity = volume;
            trade.taker_order_id = order.id;
            trade.maker_order_id = 0; // Dummy value
            trades.push_back(trade);
            if (it->second <= 0)
                bids.erase(it);
        }
    }
    return tradedVolume;
}
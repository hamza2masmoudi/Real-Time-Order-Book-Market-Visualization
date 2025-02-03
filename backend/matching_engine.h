#pragma once
#include "orderbook.h"
#include <queue>
#include <atomic>
#include <thread>
#include <condition_variable>

class MatchingEngine {
public:
    MatchingEngine();
    ~MatchingEngine();

    void start();
    void stop();
    void submit_order(const Order& order);
    OrderBook& get_order_book();
    uint64_t getProcessedOrderCount() const { return processedOrders.load(); }

private:
    void matching_thread();

    OrderBook order_book;
    std::atomic<bool> running{false};
    std::thread engine_thread;
    std::queue<Order> order_queue;
    std::mutex queue_mutex;
    std::condition_variable cv;
    std::atomic<uint64_t> processedOrders{0};
};
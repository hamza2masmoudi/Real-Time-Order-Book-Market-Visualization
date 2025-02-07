#pragma once

#include "orderbook.h"
#include <queue>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <chrono>

class MatchingEngine {
public:
    MatchingEngine();
    ~MatchingEngine();

    void start();
    void stop();
    
    void submit_order(Order order);  // Fix: Removed `const &` to allow modifications

    OrderBook& get_order_book();
    
    uint64_t getProcessedOrderCount() const;
    double getAverageLatencyMs() const;
    double getThroughputOps() const;

private:
    void matching_thread();

    OrderBook order_book;
    std::atomic<bool> running;
    std::thread engine_thread;
    std::queue<Order> order_queue;
    std::mutex queue_mutex;
    std::condition_variable cv;
    std::atomic<uint64_t> processedOrders;

    // Latency & Throughput Tracking
    std::atomic<int64_t> totalLatencyMs;
    std::atomic<uint64_t> totalLatencyCount;
    std::chrono::steady_clock::time_point engineStartTime;
};
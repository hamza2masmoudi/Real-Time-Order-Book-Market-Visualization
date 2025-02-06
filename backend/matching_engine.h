#pragma once

#include "orderbook.h"
#include <queue>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <chrono>
#include <mutex>

class MatchingEngine {
public:
    MatchingEngine();
    ~MatchingEngine();

    void start();
    void stop();

    // Accept by value so we can store submit_time
    void submit_order(Order order);

    OrderBook& get_order_book();
    uint64_t getProcessedOrderCount() const;

    // Metrics
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

    // Basic stats
    std::atomic<uint64_t> processedOrders;

    // Store latency sums as an integer (millisecond sums) for atomic fetch_add
    std::atomic<int64_t> totalLatencyMs;
    std::atomic<uint64_t> totalLatencyCount;

    // For throughput
    std::chrono::steady_clock::time_point engineStartTime;
};
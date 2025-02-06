#include "matching_engine.h"
#ifdef SPDLOG_H
#include <spdlog/spdlog.h>
#endif
#include <algorithm>

MatchingEngine::MatchingEngine()
    : running(false),
      processedOrders(0),
      totalLatencyMs(0),
      totalLatencyCount(0)
{
#ifdef SPDLOG_H
    spdlog::info("MatchingEngine constructed.");
#endif
}

MatchingEngine::~MatchingEngine() {
    stop();
}

void MatchingEngine::start() {
    running = true;
    engineStartTime = std::chrono::steady_clock::now();
    engine_thread = std::thread(&MatchingEngine::matching_thread, this);

#ifdef SPDLOG_H
    spdlog::info("MatchingEngine started.");
#endif
}

void MatchingEngine::stop() {
    running = false;
    cv.notify_all();
    if (engine_thread.joinable())
        engine_thread.join();
#ifdef SPDLOG_H
    spdlog::info("MatchingEngine stopped.");
#endif
}

void MatchingEngine::submit_order(Order order) {
    order.submit_time = std::chrono::steady_clock::now();

    if (order.price <= 0 || order.quantity <= 0) {
#ifdef SPDLOG_H
        spdlog::error("Invalid order (price={}, qty={}). Not submitted.", order.price, order.quantity);
#endif
        return;
    }

    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        order_queue.push(order);
    }

#ifdef SPDLOG_H
    spdlog::info("Order submitted. ID={}, Price={}, Qty={}, is_bid={}, type={}",
                 order.id, order.price, order.quantity, order.is_bid,
                 (order.type == OrderType::MARKET ? "MARKET" : "LIMIT"));
#endif

    cv.notify_one();
}

OrderBook& MatchingEngine::get_order_book() {
    return order_book;
}

uint64_t MatchingEngine::getProcessedOrderCount() const {
    return processedOrders.load();
}

double MatchingEngine::getAverageLatencyMs() const {
    uint64_t count = totalLatencyCount.load();
    if (count == 0) return 0.0;

    int64_t sumMs = totalLatencyMs.load();
    return static_cast<double>(sumMs) / static_cast<double>(count);
}

double MatchingEngine::getThroughputOps() const {
    auto now = std::chrono::steady_clock::now();
    double elapsedSec = std::chrono::duration_cast<std::chrono::seconds>(now - engineStartTime).count();
    if (elapsedSec < 0.001) return 0.0;

    return static_cast<double>(processedOrders.load()) / elapsedSec;
}

void MatchingEngine::matching_thread() {
#ifdef SPDLOG_H
    spdlog::info("MatchingEngine thread started.");
#endif

    while (running) {
        std::unique_lock<std::mutex> lock(queue_mutex);
        cv.wait(lock, [this]{ return !order_queue.empty() || !running; });
        if (!running) break;

        Order order = order_queue.front();
        order_queue.pop();
        lock.unlock();

        // Perform matching
        double matchedVolume = order_book.match_order(order);
        if (matchedVolume < order.quantity) {
            Order remainingOrder = order;
            remainingOrder.quantity -= matchedVolume;
            order_book.add_order(remainingOrder);
#ifdef SPDLOG_H
            spdlog::info("Order partially matched. ID={}, matched={}", order.id, matchedVolume);
#endif
        } else {
#ifdef SPDLOG_H
            spdlog::info("Order fully matched. ID={}", order.id);
#endif
        }

        // Compute latency
        auto endTime = std::chrono::steady_clock::now();
        auto latencyMs = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - order.submit_time).count();
        totalLatencyMs.fetch_add(static_cast<int64_t>(latencyMs));
        totalLatencyCount.fetch_add(1);

        // One order processed
        processedOrders.fetch_add(1);
    }

#ifdef SPDLOG_H
    spdlog::info("MatchingEngine thread stopped.");
#endif
}
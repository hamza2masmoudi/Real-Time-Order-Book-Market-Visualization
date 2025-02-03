#include "matching_engine.h"
#include <iostream>

MatchingEngine::MatchingEngine() = default;

MatchingEngine::~MatchingEngine() {
    stop();
}

void MatchingEngine::start() {
    running = true;
    engine_thread = std::thread(&MatchingEngine::matching_thread, this);
}

void MatchingEngine::stop() {
    running = false;
    cv.notify_all();
    if (engine_thread.joinable())
        engine_thread.join();
}

void MatchingEngine::submit_order(const Order& order) {
    // Risk Management: Validate order input
    if (order.price <= 0 || order.quantity <= 0) {
        std::cerr << "Error: Invalid order values. Price and quantity must be positive." << std::endl;
        return;
    }
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        order_queue.push(order);
    }
    cv.notify_one();
}

OrderBook& MatchingEngine::get_order_book() {
    return order_book;
}

void MatchingEngine::matching_thread() {
    while (running) {
        std::unique_lock<std::mutex> lock(queue_mutex);
        cv.wait(lock, [this]{ return !order_queue.empty() || !running; });
        if (!running)
            break;
        Order order = order_queue.front();
        order_queue.pop();
        lock.unlock();

        // Simple matching: add the order to the order book
        order_book.add_order(order);
        processedOrders++;
    }
}
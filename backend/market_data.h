#pragma once

#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

class MarketDataFetcher {
public:
    MarketDataFetcher();
    ~MarketDataFetcher();

    // Fetch stock price for a given symbol
    double fetchStockPrice(const std::string& symbol);

private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);
    const std::string apiKey = "EQMPTDENOP2R0CZI";  // Replace with your Alpha Vantage API Key
};  
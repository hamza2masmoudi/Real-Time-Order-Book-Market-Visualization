#include "market_data.h"
#include <iostream>
#include <sstream>

MarketDataFetcher::MarketDataFetcher() {}

MarketDataFetcher::~MarketDataFetcher() {}

size_t MarketDataFetcher::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

double MarketDataFetcher::fetchStockPrice(const std::string& symbol) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    double price = 0.0;

    std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY"
                      "&symbol=" + symbol + "&interval=1min&apikey=" + apiKey;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "Failed to fetch market data: " << curl_easy_strerror(res) << std::endl;
        } else {
            try {
                auto jsonData = nlohmann::json::parse(readBuffer);
                auto latestData = jsonData["Time Series (1min)"].begin();
                if (latestData != jsonData["Time Series (1min)"].end()) {
                    price = std::stod(latestData.value()["1. open"].get<std::string>());
                }
            } catch (const std::exception& e) {
                std::cerr << "JSON Parsing Error: " << e.what() << std::endl;
            }
        }
    }

    return price;
}
// 11th April 2025's quote processor that tracks the order book (12.4.25)
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <string>
#include <iomanip>

struct Quote {
    double price;
    int quantity;
    char side;
    std::chrono::high_resolution_clock::time_point timestamp;
};

std::vector<Quote> generateQuotes(int count){
    std::vector<Quote> quotes;
    std::random_device rd;
    std::mt19937 gen(rd());

    double mid = 100.0;

    std::uniform_real_distribution<> buyDist(mid - 1.0, mid);
    std::uniform_real_distribution<> sellDist(mid, mid + 1.0);
    std::uniform_int_distribution<> sideDist(0, 1);

auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < count; ++i) {
        Quote q;
        q.price = sellDist(gen);
        q.quantity = buyDist(gen);
        q.side = sideDist(gen) == 0 ? 'B' : 'S';
        q.timestamp = std::chrono::high_resolution_clock::now();
        quotes.push_back(q);
    }

auto end = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
std::cout << "Total time to generate: " << count << " quotes: " << duration << "µs\n";

    return quotes;
}
void processQuotes(const std::vector<Quote>& quotes) {
    int buyCount = 0, sellCount = 0;
    double highestBuy = 0.0;
    double lowestSell = std::numeric_limits<double>::max();

    double maxBuyPrice = 0.0;
    double minSellPrice = std::numeric_limits<double>::max();

    for (const auto& q : quotes) {
        if (q.side == 'B') {
            if (q.price > maxBuyPrice) maxBuyPrice = q.price;
        } else if (q.side == 'S') {
            if (q.price < minSellPrice) minSellPrice = q.price;
        }
    }

    std::cout << "Highest BUY (Bid): " << maxBuyPrice << "\n";
    std::cout << "Lowest SELL (Ask): " << minSellPrice << "\n";

    for (const auto& q : quotes) {
        std::cout << q.side << " " << q.price << "\n";
        if (q.side == 'B') {
            ++buyCount;
            if (q.price > highestBuy) highestBuy = q.price;
        } else {
            ++sellCount;
            if (q.price < lowestSell) lowestSell = q.price;
        }
    }

    if (lowestSell < highestBuy) {
        std::cout << "Spread is negative, potential crossed market!\n";
        return;
    }

    std::cout << "\nProcessed " << buyCount << " BUY quotes and " << sellCount << "SELL quotes.\n";
    std::cout << "Best BID: " << highestBuy << " | Best ASK: " << lowestSell << "\n";
    std::cout << "Spread: " << (lowestSell - highestBuy) << "\n";
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    auto quotes = generateQuotes(1000);
    processQuotes(quotes);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Processed In: " << duration.count() << "µs\n";
}
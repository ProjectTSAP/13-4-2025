//2am quote processor update with randomly generated loop, containing buy & sell side
#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <chrono>

struct Quote {
    double price;
    int quantity;
    char side;
    std::chrono::high_resolution_clock::time_point timestamp;
};

std::vector<Quote> generateQuotes(int count);

std::pair<double, double> findBestBidAsk(const std::vector<Quote>& quotes);
void printQuoteSummary(const std::vector<Quote>& quotes);
bool isCrossedMarket(double bid, double ask);

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    int quoteCount;
    std::cout << "Enter Number of Trades to Simulare: ";
    std::cin >> quoteCount;
    auto quotes = generateQuotes(quoteCount);
    printQuoteSummary(quotes);

    auto[bestBid, bestAsk] = findBestBidAsk(quotes);

    if (isCrossedMarket(bestBid, bestAsk)) {
        std::cout << "Spread is negative, Potential crossed Market detected!\n";
    } else {
        std::cout << "Spread: " << (bestAsk - bestBid) << "\n";
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Processed in: " << duration << "µs\n";
    return 0;
}

std::vector<Quote> generateQuotes(int count) {
    std::vector<Quote> quotes;
    std::random_device rd;
    std::mt19937 gen(rd());

    double mid = 100.0;
    std::uniform_real_distribution<> buyDist(mid - 1.0, mid);
    std::uniform_real_distribution<> sellDist(mid, mid + 1.0);
    std::uniform_int_distribution<> sideDist(0, 1);

    for (int i = 0; i < count; ++i) {
        Quote q;
        if (sideDist(gen) == 0) {
        q.side = 'B';
        q.price = buyDist(gen);     
        } else {
            q.side = 'S';
            q.price = sellDist(gen);
        }
        
        q.quantity = static_cast<int>(buyDist(gen));
        q.side = (q.price <= mid) ? 'B' : 'S';
        q.timestamp = std::chrono::high_resolution_clock::now();
        quotes.push_back(q);
    }

    return quotes;
}

std::pair<double, double> findBestBidAsk(const std::vector<Quote>& quotes) {
    double bestBid = 0.0;
    double bestAsk = std::numeric_limits<double>::max();

    for (const auto& q : quotes) {
        if (q.side == 'B' && q.price > bestBid) bestBid = q.price;
        if (q.side == 'S' && q.price < bestAsk) bestAsk = q.price;
    }

    return {bestBid, bestAsk};
}

void printQuoteSummary(const std::vector<Quote>& quotes) {
    int buyCount = 0, sellCount = 0;
    for (const auto& q : quotes) {
        std::cout << q.side << " " << q.price << "\n";
        (q.side == 'B') ? ++buyCount : ++sellCount;
    }
    std::cout << "\nProcessed " << buyCount << " BUY and " << sellCount << "SELL quotes.\n";
}

bool isCrossedMarket(double bid, double ask) {
    return ask < bid;
}
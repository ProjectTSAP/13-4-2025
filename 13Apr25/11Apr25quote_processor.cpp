#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
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
    std::uniform_real_distribution<> priceDist(99.0, 101.0);
    std::uniform_int_distribution<> qtyDist(1, 100);
    std::uniform_int_distribution<> sideDist(0, 1);

auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < count; ++i) {
        Quote q;
        q.price = priceDist(gen);
        q.quantity = qtyDist(gen);
        q.side = sideDist(gen) == 0 ? 'B' : 'S';
        q.timestamp = std::chrono::high_resolution_clock::now();
        quotes.push_back(q);
    }

auto end = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
std::cout << "Total time to generate: " << count << " quotes: " << duration << "µs\n";
 
    return quotes;
}
void processQuotes(const std::vector<Quote>& quotes) {
    for(const auto& q: quotes) {
        if(q.price <= 0 || q.quantity <= 0) continue;

        std::cout << "[" << (q.side == 'B' ? "BUY" : "SELL")
                  << "] Price: " <<  std::fixed << std::setprecision(2)
                  << q.price << " | Qty: " << q.quantity << "\n";
    }
}


int main() {
    auto start = std::chrono::high_resolution_clock::now();
    auto quotes = generateQuotes(1000);
    processQuotes(quotes);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    std::cout << "Processed In: " << duration.count() << "µs\n";

    return 0;
}
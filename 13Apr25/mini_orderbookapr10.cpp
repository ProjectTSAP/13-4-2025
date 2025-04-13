#include <iostream>
#include <map>
#include <set>
#include <chrono>

using orderID = int;

struct Order {
    double price;
    int quantity;
    orderID id;
};

std::map<double, std::set<orderID>, std::greater<double>> bids;
std::map<double, std::set<orderID>> asks;
std::map<orderID, Order> allOrders;

void insertOrder(double price, int quantity, orderID id, bool isBuy) {
    Order order{price, quantity, id};
    allOrders[id] = order;

    if (isBuy) {
        bids[price].insert(id);
    } else {
        asks[price].insert(id);
    }
}

void cancelOrder(orderID id) {
    if (allOrders.count(id)) {
        auto& order = allOrders[id];
        if (bids.count(order.price)) bids[order.price].erase(id);
        if (asks.count(order.price)) asks[order.price].erase(id);
        allOrders.erase(id);
    }
}
void printTopOfBook() {
    if (!bids.empty()) {
        std::cout << "best bid: " << bids.begin()->first << " (" << bids.begin()->second.size() << "orders)\n";
    }
    if (!asks.empty()) {
        std::cout << "best ask: " << asks.begin()->first << " (" << asks.begin()->second.size() << "orders)\n";
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    insertOrder(101.5, 100, 1, true);
    insertOrder(102.0, 50, 2, true);
    insertOrder(103.0, 70, 3, true);
    insertOrder(104.0, 10, 4, false);
    insertOrder(105.0, 20, 5, false);

    cancelOrder(3);

    printTopOfBook();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Execution Time: " << duration.count() << "s\n";

    return 0;
}
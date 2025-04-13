#include <iostream>
#include <chrono>
#include <vector>

int main() {
    const size_t N = 1'000'000;
    std::vector<int> v(N, 1);

    auto start = std::chrono::high_resolution_clock::now();

    long long sum = 0;
    for (size_t i = 0; i < N; ++i){
        sum += v[i];
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> elapsed = end - start;

    std::cout << "loop completed in: " << elapsed.count() << "ns\n";
    std::cout << "Total sum: " << sum << "\n";

    return 0;
}
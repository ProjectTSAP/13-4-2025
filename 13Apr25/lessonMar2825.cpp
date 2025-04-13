// hft lesson 1

#include <iostream>
#include <cstdint>
#include <chrono>

int main() {
    int64_t sum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    //A sim of 1million price ticks
    for (int i= 0; i < 1000000; ++i) {
        sum +=i;    
    }


auto end = std::chrono::high_resolution_clock::now();

std::chrono::duration<double, std::nano> elapsed = end - start;

std::cout << "Sum: " << sum<< "\n";
std::cout << "Elapsed time: "<< elapsed.count() << "ns\n";
}
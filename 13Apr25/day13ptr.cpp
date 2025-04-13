#include <iostream>
#include <fstream>
using namespace std;

int main() {
    double prices[4] = {100.5, 101.0, 102.3, 99.8};

    ofstream outFile("prices.csv");

    if (outFile.is_open()) {
        outFile << "Price\n";
        for (int i = 0; i < 4; i++) {
            outFile << prices[i] << "\n";
        }
        outFile.close();
        cout << "Prices exported to prices.csv\n";
    } else {
        cout << "Error opening file for writing.\n";
    }

    double* ptr = prices;
    while (ptr < prices + 4) {
        cout << *ptr << " ";
        ptr++;
    }
    
    cout << endl;

    double* array = prices;
    int size = 4;

    double sum = 0;
    double* end = array + size;
    while (array < end) {
        sum += *array;
        array++;
    }
    cout << "Average Price: " << sum / size << endl;
    return 0;
}
#include <iostream>
using namespace std;

void doubleIt(int& x) {
    x *= 2;
}

int main() {
    int val = 7;
    cout << "Before: " << val << endl;

    doubleIt(val);

    cout << "After" << val << endl;
    return 0;
}
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main() {
    // n 为年数，i 为年利率
    int n;
    double i, value = 0, input;
    cin >> n >> i;
    for (int j = 0; j < n + 1; j++) {
        cin >> input;
        value += input * pow((1 + i), -j);
    }
    cout << value << endl;
    return 0;
}
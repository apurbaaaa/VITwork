#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

int maxLength(int a, int b) {
    return max(to_string(a).length(), to_string(b).length());
}

pair<int, int> splitNumber(int num, int n) {
    int power = pow(10, n / 2);
    int low = num % power;
    int high = num / power;
    return make_pair(high, low);
}

int karatsuba(int x, int y) {
    int length = maxLength(x, y);

    if (length == 1) {
        return x * y;
    }

    int n = length;
    int half = n / 2;

    pair<int, int> x_split = splitNumber(x, n);
    pair<int, int> y_split = splitNumber(y, n);

    int high1 = x_split.first, low1 = x_split.second;
    int high2 = y_split.first, low2 = y_split.second;

    int z0 = karatsuba(low1, low2);
    int z1 = karatsuba(low1 + high1, low2 + high2);
    int z2 = karatsuba(high1, high2);

    return (z2 * pow(10, 2 * half)) + ((z1 - z2 - z0) * pow(10, half)) + z0;
}

int main() {
    int x, y;

    cout << "Enter first number: ";
    cin >> x;
    cout << "Enter second number: ";
    cin >> y;

    int max_len = maxLength(x, y);
    cout << "Maximum length of numbers: " << max_len << endl;

    int result = karatsuba(x, y);
    cout << "Product of the numbers using Karatsuba multiplication: " << result << endl;

    return 0;
}

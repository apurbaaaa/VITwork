#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}


int getPhi(int n) {
    if (isPrime(n)) {
        return n - 1;  
    }
 
    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            int q = n / p;
            if (isPrime(q) && isPrime(q)) {
                cout << "p = " << p << "\tq = " << q << "\n";
                return (p - 1) * (q - 1); 
            }
        }
    }

    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            result -= result / i;
        }
    }
    if (n > 1) {
        result -= result / n;
    }
    return result;
}

void eulers(int a, int b, int n) {
    int phin = getPhi(n);
    cout << "phi(n) = " << phin << "\n";
    int rem = b % phin;
    int result = pow(a, rem);
    int answer = fmod(result, n);
    cout << "Answer = " << answer << endl;
}

int main() {
    int a, b, n;
    cout << "Enter a, b, and n to compute a^b MOD n: ";
    cin >> a >> b >> n;

    if (gcd(a, n) != 1) {
        cout << "Euler's theorem cannot be applied because gcd(a, n) != 1.\n";
        return 1;
    }

    eulers(a, b, n);
    return 0;
}

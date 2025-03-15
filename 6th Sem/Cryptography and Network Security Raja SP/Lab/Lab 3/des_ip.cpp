#include <iostream>
#include <bitset>
using namespace std;


int IP[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};


bitset<64> initialPermutation(bitset<64> input) {
    bitset<64> permuted;
    for (int i = 0; i < 64; i++) {
        permuted[63 - i] = input[64 - IP[i]]; 
    }
    return permuted;
}

int main() {
    uint64_t input;
    cout << "Enter a 64-bit number (in hex): ";
    cin >> hex >> input;
    
    bitset<64> inputBits(input);
    cout << "Original 64-bit input:  " << inputBits << endl;
    
    bitset<64> permutedBits = initialPermutation(inputBits);
    cout << "After Initial Permutation: " << permutedBits << endl;
    
    return 0;
}

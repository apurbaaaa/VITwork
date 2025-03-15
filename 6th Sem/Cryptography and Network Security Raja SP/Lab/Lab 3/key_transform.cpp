#include <iostream>
#include <bitset>
using namespace std;
//g++ key_transform.cpp -o key_transform

int PC1[56] = {
    57, 49, 41, 33, 25, 17, 9, 1,
    58, 50, 42, 34, 26, 18, 10, 2,
    59, 51, 43, 35, 27, 19, 11, 3,
    60, 52, 44, 36, 63, 55, 47, 39,
    31, 23, 15, 7, 62, 54, 46, 38,
    30, 22, 14, 6, 61, 53, 45, 37,
    29, 21, 13, 5, 28, 20, 12, 4
};

int PC2[48] = {
    14, 17, 11, 24, 1, 5, 3, 28,
    15, 6, 21, 10, 23, 19, 12, 4,
    26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
};


int shiftSchedule[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};


bitset<56> permutePC1(bitset<64> key) {
    bitset<56> permutedKey;
    for (int i = 0; i < 56; i++) {
        permutedKey[55 - i] = key[64 - PC1[i]];
    }
    return permutedKey;
}


bitset<48> permutePC2(bitset<56> combinedCD) {
    bitset<48> subKey;
    for (int i = 0; i < 48; i++) {
        subKey[47 - i] = combinedCD[56 - PC2[i]];
    }
    return subKey;
}

bitset<28> leftCircularShift(bitset<28> half, int shifts) {
    return (half << shifts) | (half >> (28 - shifts));
}

int main() {
    uint64_t inputKey;
    int roundNumber;
    
    cout << "Enter 64-bit key (in hexadecimal): ";
    cin >> hex >> inputKey;
    cout << "Enter round number (1-16): ";
    cin >> roundNumber;
    
    if (roundNumber < 1 || roundNumber > 16) {
        cout << "Invalid round number. Must be between 1 and 16." << endl;
        return 1;
    }
    
    bitset<64> key(inputKey);
    bitset<56> permutedKey = permutePC1(key);
    

    bitset<28> C, D;
    for (int i = 0; i < 28; i++) {
        C[27 - i] = permutedKey[55 - i];
        D[27 - i] = permutedKey[27 - i];
    }
    

    int shifts = shiftSchedule[roundNumber - 1];
    C = leftCircularShift(C, shifts);
    D = leftCircularShift(D, shifts);

    bitset<56> combinedCD = (C.to_ullong() << 28) | D.to_ullong();
    

    bitset<48> roundKey = permutePC2(combinedCD);
    

    cout << "Round " << roundNumber << " Key: " << roundKey << endl;
    return 0;
}
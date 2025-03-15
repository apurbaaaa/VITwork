#include <iostream>
#include <bitset>
using namespace std;


int E[48] = {
    32, 1, 2, 3, 4, 5, 4, 5,
    6, 7, 8, 9, 8, 9, 10, 11,
    12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21,
    22, 23, 24, 25, 24, 25, 26, 27,
    28, 29, 28, 29, 30, 31, 32, 1
};


int SBox[8][4][16] = {

    {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
     {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
     {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
     {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
};

int P[32] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};


bitset<48> expand(bitset<32> R) {
    bitset<48> expanded;
    for (int i = 0; i < 48; i++) {
        expanded[47 - i] = R[32 - E[i]];
    }
    return expanded;
}


bitset<32> sBoxSubstitution(bitset<48> input) {
    bitset<32> output;
    for (int i = 0; i < 8; i++) {
        int row = (input[47 - (i * 6)] << 1) | input[47 - (i * 6 + 5)];
        int col = (input[47 - (i * 6 + 1)] << 3) | (input[47 - (i * 6 + 2)] << 2) |
                  (input[47 - (i * 6 + 3)] << 1) | input[47 - (i * 6 + 4)];
        int value = SBox[i][row][col];
        for (int j = 0; j < 4; j++) {
            output[31 - (i * 4 + j)] = (value >> (3 - j)) & 1;
        }
    }
    return output;
}


bitset<32> permute(bitset<32> input) {
    bitset<32> output;
    for (int i = 0; i < 32; i++) {
        output[31 - i] = input[32 - P[i]];
    }
    return output;
}

int main() {

    bitset<64> input("0000000100100011010001010110011110001001101010111100110111101111");
    bitset<48> roundKey("000110110000001011101111111111000111000001110010");
    

    bitset<32> L, R;
    for (int i = 0; i < 32; i++) {
        L[i] = input[i + 32];
        R[i] = input[i];
    }
    
    bitset<48> expandedR = expand(R);
    
    bitset<48> xorResult = expandedR ^ roundKey;
    
    bitset<32> sBoxOutput = sBoxSubstitution(xorResult);
    
    bitset<32> permutedOutput = permute(sBoxOutput);
    
    bitset<32> newR = L ^ permutedOutput;
    bitset<32> newL = R;
    
    bitset<64> finalOutput;
    for (int i = 0; i < 32; i++) {
        finalOutput[i + 32] = newL[i];
        finalOutput[i] = newR[i];
    }
    
    cout << "L: " << L << endl;
    cout << "R: " << R << endl;
    cout << "Expanded R: " << expandedR << endl;
    cout << "XOR Result: " << xorResult << endl;
    cout << "S-Box Output: " << sBoxOutput << endl;
    cout << "Permuted Output: " << permutedOutput << endl;
    cout << "New R: " << newR << endl;
    cout << "Final 64-bit Output: " << finalOutput << endl;
    
    return 0;
}

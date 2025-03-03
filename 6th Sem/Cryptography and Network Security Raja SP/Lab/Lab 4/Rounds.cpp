#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cstdint>

using namespace std;

typedef vector<vector<uint8_t>> Matrix;


const uint8_t S_BOX[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2
};


Matrix hexToMatrix(const string &hex) {
    Matrix state(4, vector<uint8_t>(4));
    for (int i = 0; i < 16; i++) {
        string byteString = hex.substr(i * 2, 2);
        state[i % 4][i / 4] = stoi(byteString, nullptr, 16);
    }
    return state;
}


void printMatrix(const Matrix &state) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << hex << setw(2) << setfill('0') << (int)state[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


void subBytes(Matrix &state) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[i][j] = S_BOX[state[i][j]];
        }
    }
}


void shiftRows(Matrix &state) {
    for (int i = 1; i < 4; i++) {
        vector<uint8_t> tempRow = state[i];
        for (int j = 0; j < 4; j++) {
            state[i][j] = tempRow[(j + i) % 4];
        }
    }
}

uint8_t gmul(uint8_t a, uint8_t b) {
    uint8_t p = 0;
    while (b) {
        if (b & 1) p ^= a;
        a = (a << 1) ^ ((a & 0x80) ? 0x1B : 0);
        b >>= 1;
    }
    return p;
}


void mixColumns(Matrix &state) {
    const uint8_t mix[4][4] = {
        {2, 3, 1, 1},
        {1, 2, 3, 1},
        {1, 1, 2, 3},
        {3, 1, 1, 2}
    };

    Matrix temp(4, vector<uint8_t>(4));
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            temp[r][c] = gmul(mix[r][0], state[0][c]) ^
                         gmul(mix[r][1], state[1][c]) ^
                         gmul(mix[r][2], state[2][c]) ^
                         gmul(mix[r][3], state[3][c]);
        }
    }
    state = temp;
}


void addRoundKey(Matrix &state, const Matrix &roundKey) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[i][j] ^= roundKey[i][j];
        }
    }
}


void aesRound(Matrix &state, const Matrix &roundKey) {
    subBytes(state);
    shiftRows(state);
    mixColumns(state);
    addRoundKey(state, roundKey);
}

int main() {
    string plaintextHex, keyHex;
    
    cout << "Enter 16-byte plaintext in hex (32 characters): ";
    cin >> plaintextHex;
    cout << "Enter 16-byte key in hex (32 characters): ";
    cin >> keyHex;

    if (plaintextHex.length() != 32 || keyHex.length() != 32) {
        cerr << "Invalid input! Must be exactly 32 hex characters (16 bytes)." << endl;
        return 1;
    }

    Matrix state = hexToMatrix(plaintextHex);
    Matrix roundKey = hexToMatrix(keyHex);

    cout << "\nInitial State:\n";
    printMatrix(state);

    aesRound(state, roundKey);

    cout << "State after AES round:\n";
    printMatrix(state);

    return 0;
}

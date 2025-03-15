#include <iostream>
using namespace std;

const int N = 4;

unsigned char gmul(unsigned char a, unsigned char b) {
    unsigned char p = 0;
    for (int i = 0; i < 8; i++) {
        if (b & 1)
            p ^= a;
        bool hiBitSet = (a & 0x80);
        a <<= 1;
        if (hiBitSet)
            a ^= 0x1B; 
        b >>= 1;
    }
    return p;
}

void mixColumns(unsigned char state[N][N]) {
    unsigned char temp[N][N];

    for (int c = 0; c < N; c++) {
        temp[0][c] = gmul(0x02, state[0][c]) ^ gmul(0x03, state[1][c]) ^ state[2][c] ^ state[3][c];
        temp[1][c] = state[0][c] ^ gmul(0x02, state[1][c]) ^ gmul(0x03, state[2][c]) ^ state[3][c];
        temp[2][c] = state[0][c] ^ state[1][c] ^ gmul(0x02, state[2][c]) ^ gmul(0x03, state[3][c]);
        temp[3][c] = gmul(0x03, state[0][c]) ^ state[1][c] ^ state[2][c] ^ gmul(0x02, state[3][c]);
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            state[i][j] = temp[i][j];
}

void printState(unsigned char state[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%02X ", state[i][j]);
        }
        cout << endl;
    }
}

int main() {
    unsigned char state[N][N];

    cout << "Enter 16 bytes (in hex) for the AES state matrix (row-wise):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int val;
            cin >> hex >> val; 
            state[i][j] = static_cast<unsigned char>(val);
        }
    }

    cout << "\nOriginal State Matrix:\n";
    printState(state);

    mixColumns(state);

    cout << "\nState Matrix After MixColumns:\n";
    printState(state);

    return 0;
}

#include <iostream>
using namespace std;

const int N = 4;

void shiftRows(unsigned char state[N][N]) {
    unsigned char temp;

    temp = state[1][0];
    for (int i = 0; i < N - 1; i++)
        state[1][i] = state[1][i + 1];
    state[1][N - 1] = temp;

    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;

    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;

    temp = state[3][N - 1];
    for (int i = N - 1; i > 0; i--)
        state[3][i] = state[3][i - 1];
    state[3][0] = temp;
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

    shiftRows(state);

    cout << "\nState Matrix After ShiftRows:\n";
    printState(state);

    return 0;
}

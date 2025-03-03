#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

vector<uint8_t> hexStringToBytes(const string &hex) {
    vector<uint8_t> bytes;
    for (size_t i = 0; i < hex.length(); i += 2) {
        string byteStr = hex.substr(i, 2);
        bytes.push_back(stoul(byteStr, nullptr, 16));
    }
    return bytes;
}

vector<vector<uint8_t>> createStateMatrix(const vector<uint8_t> &bytes) {
    vector<vector<uint8_t>> state(4, vector<uint8_t>(4));
    int index = 0;
    for (int col = 0; col < 4; col++)
        for (int row = 0; row < 4; row++)
            state[row][col] = bytes[index++];
    return state;
}

void addRoundKey(vector<vector<uint8_t>> &state, const vector<uint8_t> &roundKey) {
    for (int col = 0; col < 4; col++)
        for (int row = 0; row < 4; row++)
            state[row][col] ^= roundKey[row + col * 4];
}

void printState(const vector<vector<uint8_t>> &state) {
    for (const auto &row : state) {
        for (uint8_t byte : row)
            cout << hex << setw(2) << setfill('0') << (int)byte << " ";
        cout << endl;
    }
}

int main() {
    string plaintextHex, keyHex;
    cout << "Enter a 16-byte plaintext (32 hex characters): ";
    cin >> plaintextHex;
    cout << "Enter the first round key (from key expansion, 32 hex characters): ";
    cin >> keyHex;

    vector<uint8_t> plaintext = hexStringToBytes(plaintextHex);
    vector<uint8_t> key = hexStringToBytes(keyHex);
    
    vector<vector<uint8_t>> state = createStateMatrix(plaintext);
    addRoundKey(state, key);

    cout << "After Initial AddRoundKey:\n";
    printState(state);

    return 0;
}

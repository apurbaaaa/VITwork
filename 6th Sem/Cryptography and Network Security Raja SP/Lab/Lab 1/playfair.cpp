#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define SIZE 30

void generateKeyMatrix(const string &key, char keyMatrix[5][5]) {
    bool seen[26] = {false};
    int row = 0, col = 0;

    for (int i = 0; i < key.length(); i++) {
        char ch = key[i];
        if (ch == 'j') ch = 'i';
        if (!seen[ch - 'a']) {
            keyMatrix[row][col++] = ch;
            seen[ch - 'a'] = true;
            if (col == 5) { row++; col = 0; }
        }
    }

    for (char ch = 'a'; ch <= 'z'; ch++) {
        if (ch == 'j') continue;
        if (!seen[ch - 'a']) {
            keyMatrix[row][col++] = ch;
            seen[ch - 'a'] = true;
            if (col == 5) { row++; col = 0; }
        }
    }
}

void findPosition(char keyMatrix[5][5], char ch, int &row, int &col) {
    if (ch == 'j') ch = 'i';
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (keyMatrix[i][j] == ch) {
                row = i; col = j;
                return;
            }
        }
    }
}

void prepareText(string &text) {
    if (text.length() % 2 != 0) text += 'z';
}

void encryptText(string &text, char keyMatrix[5][5]) {
    for (size_t i = 0; i < text.length(); i += 2) {
        int r1, c1, r2, c2;
        findPosition(keyMatrix, text[i], r1, c1);
        findPosition(keyMatrix, text[i + 1], r2, c2);

        if (r1 == r2) {
            text[i] = keyMatrix[r1][(c1 + 1) % 5];
            text[i + 1] = keyMatrix[r2][(c2 + 1) % 5];
        } else if (c1 == c2) {
            text[i] = keyMatrix[(r1 + 1) % 5][c1];
            text[i + 1] = keyMatrix[(r2 + 1) % 5][c2];
        } else {
            text[i] = keyMatrix[r1][c2];
            text[i + 1] = keyMatrix[r2][c1];
        }
    }
}

void decryptText(string &text, char keyMatrix[5][5]) {
    for (size_t i = 0; i < text.length(); i += 2) {
        int r1, c1, r2, c2;
        findPosition(keyMatrix, text[i], r1, c1);
        findPosition(keyMatrix, text[i + 1], r2, c2);

        if (r1 == r2) {
            text[i] = keyMatrix[r1][(c1 - 1 + 5) % 5]; 
            text[i + 1] = keyMatrix[r2][(c2 - 1 + 5) % 5];  
        } else if (c1 == c2) {
            text[i] = keyMatrix[(r1 - 1 + 5) % 5][c1];
            text[i + 1] = keyMatrix[(r2 - 1 + 5) % 5][c2];  
        } else {
            text[i] = keyMatrix[r1][c2];
            text[i + 1] = keyMatrix[r2][c1];
        }
    }
}

void toLowerCase(string &text) {
    for (size_t i = 0; i < text.length(); i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = text[i] + 'a' - 'A';  
        }
    }
}

int main() {
    string plaintext, key;
    cout << "Enter plaintext: ";
    cin >> plaintext;
    cout << "Enter key: ";
    cin >> key;

    toLowerCase(plaintext);
    toLowerCase(key);

    char keyMatrix[5][5];
    generateKeyMatrix(key, keyMatrix);
    prepareText(plaintext);

    string ciphertext = plaintext;
    encryptText(ciphertext, keyMatrix);
    cout << "Cipher text: " << ciphertext << endl;


    decryptText(ciphertext, keyMatrix);
    cout << "Decrypted text: " << ciphertext << endl;

    return 0;
}

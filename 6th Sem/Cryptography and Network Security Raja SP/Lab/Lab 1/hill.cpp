#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> performMatrixMultiplication(vector<vector<int>> &matrix, vector<int> &vectorInput, int mod) {
    vector<int> result(2);
    for (int row = 0; row < 2; row++) {
        result[row] = 0;
        for (int col = 0; col < 2; col++) {
            result[row] += matrix[row][col] * vectorInput[col];
        }
        result[row] = (result[row] % mod + mod) % mod;
    }
    return result;
}

string encryptMessage(string plainText, vector<vector<int>> &keyMatrix) {
    string encryptedText = "";
    int textLength = plainText.size();
    if (textLength % 2 != 0) {
        plainText += 'X';
    }
    for (size_t i = 0; i < plainText.size(); i += 2) {
        vector<int> letterVector = {plainText[i] - 'A', plainText[i + 1] - 'A'};
        vector<int> encryptedVector = performMatrixMultiplication(keyMatrix, letterVector, 26);
        encryptedText += (encryptedVector[0] + 'A');
        encryptedText += (encryptedVector[1] + 'A');
    }
    return encryptedText;
}

int main() {
    string plainText;
    cout << "Enter the message to encrypt (uppercase letters only): ";
    cin >> plainText;

    int matrixSize;
    cout << "Enter the size of the key matrix (e.g., 2 for a 2x2 matrix): ";
    cin >> matrixSize;

    vector<vector<int>> encryptionKey(matrixSize, vector<int>(matrixSize));
    cout << "Enter the elements of the key matrix row by row:\n";
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            cin >> encryptionKey[i][j];
        }
    }

    string encryptedText = encryptMessage(plainText, encryptionKey);
    cout << "Encrypted message: " << encryptedText << endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> performMatrixMultiplication(vector<vector<int> > &matrix,
                                        vector<int> &vectorInput, int mod) {
    int size = matrix.size();
    vector<int> result(size, 0);
    
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            result[row] += matrix[row][col] * vectorInput[col];
        }
        result[row] = (result[row] % mod + mod) % mod;
    }
    return result;
}

string encryptMessage(string plainText, vector<vector<int> > &keyMatrix, int matrixSize) {
    string encryptedText = "";

    while (plainText.size() % matrixSize != 0) {
        plainText += 'X';
    }

    for (size_t i = 0; i < plainText.size(); i += matrixSize) {
        vector<int> letterVector(matrixSize);
        
        for (int j = 0; j < matrixSize; j++) {
            letterVector[j] = plainText[i + j] - 'A';
        }

        vector<int> encryptedVector = performMatrixMultiplication(keyMatrix, letterVector, 26);

        for (int j = 0; j < matrixSize; j++) {
            encryptedText += (encryptedVector[j] + 'A');
        }
    }

    return encryptedText;
}

int main() {
    string plainText;
    cout << "Enter the message to encrypt (uppercase letters only): ";
    cin >> plainText;

    int matrixSize;
    cout << "Enter key matrix size: ";
    cin >> matrixSize;

    vector<vector<int> > encryptionKey(matrixSize, vector<int>(matrixSize));

    cout << "Enter the elements of key matrix:\n";
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            cin >> encryptionKey[i][j];
        }
    }

    string encryptedText = encryptMessage(plainText, encryptionKey, matrixSize);
    cout << "Encrypted message: " << encryptedText << endl;

    return 0;
}

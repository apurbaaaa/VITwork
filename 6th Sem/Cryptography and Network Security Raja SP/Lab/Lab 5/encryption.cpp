#include <iostream>
#include <vector>

using namespace std;

void printVector(const vector<int>& vec) {
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

vector<int> rc4_encrypt(vector<int>& plaintext, vector<int>& keystream) {
    vector<int> ciphertext;
    for (size_t i = 0; i < plaintext.size(); i++) {
        ciphertext.push_back(plaintext[i] ^ keystream[i]);  
    }
    return ciphertext;
}

int main() {
    
    int plaintextSize;
    cout << "Enter plaintext size: \n";
    cin >> plaintextSize;
    vector<int> PT(plaintextSize), K(plaintextSize);
    cout<< "Enter plaintext: \n";
    for (int i = 0; i< plaintextSize; i++){
        cin>> PT[i];
    }

    cout<< "Input Generated Keystream: \n";
    for (int i = 0; i< plaintextSize; i++){
        cin>> K[i];
    }

    vector<int> CT =  rc4_encrypt(PT, K);
    cout << "Ciphertext: ";
    printVector(CT);
    return 0;
}

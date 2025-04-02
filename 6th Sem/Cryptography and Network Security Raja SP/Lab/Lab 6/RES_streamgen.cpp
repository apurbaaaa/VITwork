#include <iostream>
#include <vector>

using namespace std;

void printS(const vector<int>& S) {
    for (int val : S) {
        cout << val << " ";
    }
    cout << endl;
}

void rc4_keystream(vector<int>& S, int numBytes) {
    int i = 0, j = 0;

    cout << "Generated Keystream:\n";
    for (int count = 0; count < numBytes; count++) {
        i = (i + 1) % 8;
        j = (j + S[i]) % 8;

        swap(S[i], S[j]); 

        int t = (S[i] + S[j]) % 8; 
        int k = S[t]; 

        cout << k << " "; 
    }
    cout << endl;
}

int main() {
    vector<int> S(8);
    cout<<"Enter S vector: \n";
    for (int i = 0; i<8; i++){
        cin>>S[i];
    }

    cout << "Initial S: ";
    printS(S);

    int numBytes;
    cout << "Enter number of keys to generate: ";
    cin >> numBytes;

    rc4_keystream(S, numBytes);

    return 0;
}

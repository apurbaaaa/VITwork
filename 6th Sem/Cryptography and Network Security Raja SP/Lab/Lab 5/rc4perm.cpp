#include <iostream>
#include <vector>

using namespace std;

void printS(const vector<int>& S) {
    for (int val : S) {
        cout << val << " ";
    }
    cout << endl;
}

void rc4_permutation(vector<int>& S, const vector<int>& T) {
    int j = 0;
    for (int i = 0; i < 8; i++) {
        j = (j + S[i] + T[i]) % 8;
        swap(S[i], S[j]);
        cout << "Iteration " << i << ": ";
        printS(S);
    }
}

int main() {
    //in this program, we are running the RC4 algorithm to 8 bits, as taking 256 bits would be very difficult to assess, same as class
    int keysize;
    cout<<"Enter Key size: \n";
    cin>>keysize;
    if (keysize < 1 || keysize > 8) {
        cout << "Invalid key size. Must be between 1 and 8.\n";
        return 1;
    }
    vector<int> S(8), T(8), key(keysize);
    cout<<"Enter Key:\n";
    for (int i = 0; i < keysize; i++){
        cin>>key[i];
    }

    

    for (int i = 0; i < 8; i++) {
        S[i] = i;
        T[i] = key[i % keysize];  
    }

    rc4_permutation(S, T);

    cout << "S after permutation:\n";
    for (int i = 0; i < 8; i++) {
        cout << S[i] << " ";
    }
    cout << endl;

    return 0;
}

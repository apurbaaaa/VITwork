#include <iostream>
#include <cmath>
using namespace std;
int calculateYa(int a, int Xa, int q){
    return (static_cast<long long>(pow(a, Xa)))%q;
}
bool primitive(int q, int a) {
    if (q <= 1 || a <= 1 || a >= q) {
        return false;  
    }

    for (int i = 1; i < q; i++) {
        if (pow(a, i) - (int)(pow(a, i) / q) * q == 0) {  
            return false;  
        }
    }
    return true; 
}
int calculateK(int Ya, int k, int q){
    return (static_cast<long long>(pow(Ya, k)))%q;
}
int calculateC1(int a, int k, int q){
    return (static_cast<long long>(pow(a, k)))%q;
}
int calculateC2(int K, int M, int q){
    return (K * M) % q;
}
int checkNeg(int t2, int phi){
    if (t2 > 0){
        return t2;
    }
    else{
        int temp = abs(t2);
        int m = temp % phi;
        t2 = (phi - m) % phi;
        return t2;
    }
}
int inverse(int q, int r1, int r2, int t1, int t2){
    int r = r1 % r2;
    int qa = r1/r2;
    int t = t1 - t2 * qa;
    if (r2 == 1 && r == 0){
        t2 = checkNeg(t2, q);
        return t2;
    }
    else{
        return inverse(q, r2, r, t2, t);
    }
}
int main(){
    int q, a;
    cout<<"Enter prime numbers q and a, such that a is a primitive root of q: \n";
    cin>>q;
    cin>>a;
    if(!primitive(q, a)){
        return 1;
    }
    int Xa, Ya;
    cout<<"Enter private key: \n";
    cin>>Xa;
    Ya = calculateYa(a, Xa, q);
    cout<<"Ya: "<<Ya<<"\n";
    cout<<"Choose k\n";
    int k;
    cin>>k;
    int K = calculateK(Ya, k, q);
    int c1, c2, M;
    
    cout<<"Enter Message: \n";
    cin>>M;
    
    c1 = calculateC1(a, k, q);
    c2 = calculateC2(K, M, q);
    cout<<"C1 and C2: ("<<c1<<", "<<c2<<")\n"<<"Decryption:\n"<<"Recover K\n";
    K = calculateK(c1, Xa, q);
    cout<<"K: "<<K<<"\n"<<"Recovering M:\n"<< "M:" ;
    M = (c2 * inverse(q, q, K, 0, 1))% q;
    cout<<M<<"\n";
    return 0;
}
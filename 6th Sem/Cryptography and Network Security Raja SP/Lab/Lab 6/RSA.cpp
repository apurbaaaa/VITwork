#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}
int getPhi(int N, int P, int Q){
    int result = N;
    if(isPrime(P) && isPrime(Q)){
        return (P-1) * (Q-1);
    }
    
    else{
        
        for (int i = 2; i * i <= N; i++){
            while (N % i == 0){
                N /= i;

            }
            result = result - (result/i);
        }
    }
    if(N > 1){
        result -= result / N;
    }
    return result;
}
int Eulers(int CT, int D, int N, int P, int Q) {
    int phin = getPhi(N, P, Q);


    int rem = D % phin;

    //used successive squaring
    int result = 1;
    for (int i = 0; i < rem; i++) {
        result = (result * CT) % N;  
    }

    return result;
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
int calculateD(int phi, int r1, int r2, int t1, int t2){
    int r = r1 % r2;
    int q = r1/r2;
    int t = t1 - t2 * q;
    if (r2 == 1 && r == 0){
        t2 = checkNeg(t2, phi);
        return t2;
    }
    else{
        return calculateD(phi, r2, r, t2, t);
    }
}
int main(){
    int P, Q;
    cout<<"Enter two prime number, P and Q: \n";
    cin>>P;
    cin>>Q;
    int N = P * Q;
    cout<<"N: "<<N<<"\n";
    int phi = getPhi(N, P, Q);
    cout<<"Enter Public Key E for Encryption: \n";
    int E;
    cin>>E;
    cout<<"Finding private key D for decryption using formula (D * E) MOD phi(N) = 1\n";
    int D;
    D = calculateD(phi, phi, E, 0, 1);

    cout<<"Calculated D value: "<<D<<"\n";

    long long CT, PT;
    cout<<"Enter Message to be encrypted such that it is smaller than P * Q: \n";   
    cin>>PT;
    CT = (static_cast<long long>(pow(PT, E))) % N;
    cout<<"Cipher Text: "<< CT<<"\nDecrypting:\n";
    PT = Eulers(CT, D, N, P, Q);
    cout<<"Decrypted Text: "<< PT;
}
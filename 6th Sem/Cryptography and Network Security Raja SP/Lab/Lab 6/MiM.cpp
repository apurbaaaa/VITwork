#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int g, n, xa, A, yb, B, xc, yc, Ac, Bc, K1, K2, K1p, K2p;
    cout<<"Enter g and n:\n";
    cin>>g>>n;
    cout<<"Enter private key of A\n";
    cin>>xa;
    A = (static_cast<long long>(pow(g, xa))) % n;
    cout<<"Enter private key of B\n";
    cin>>yb;

    B = (static_cast<long long>(pow(g, yb))) % n;
    cout<<"A: "<<A<<" B: "<<B<<"\n";
    cout<<"Enter x and y used by the attacker:\n";
    cin>>xc>>yc;
    cout<<"A and B values calculated by the attacker: ";
    Ac = (static_cast<long long>(pow(g, xc))) % n;
    Bc = (static_cast<long long>(pow(g, yc))) % n;
    cout<<"Ac: "<<Ac<<" Bc: "<<Bc<<"\n";
    cout<<"K1 and K2 values calculated by the attacker: ";
    K1 = (static_cast<long long>(pow(Bc, xa))) % n;
    K2 = (static_cast<long long>(pow(Ac, yb))) % n;
    cout<<"K1: "<<K1<<" K2: "<<K2<<"\n";
    cout<<"K1* and K2* values calculated by the attacker: ";
    K1p = (static_cast<long long>(pow(B, xc))) % n;
    K2p = (static_cast<long long>(pow(A, yc))) % n;
    cout<<"K1*: "<<K1p<<" K2*: "<<K2p<<"\n";
    if(K1p == K2 && K2p == K1){
        cout<<"Man in the middle attack shown in diffie hellman as K1 = K2* and K2 = K1*";
    }
    else{
        cout<<"Attack failed";
    }
    return 0;

}
#include <iostream>
#include <cmath> 
using namespace std;

bool prime(int p){
    if(p<=1){
        return false;
    }
    for (int i = 2; i <= sqrt(p); i++){
        if(p%i == 0){
            return false;
        }
    }
    return true;
}

int gcd(int a, int b) {
    if (b == 0) {
        return a; 
    }
    return gcd(b, a % b);
}

void fermats(int a, int b, int p){
    if (b == p-1){
        cout<<"Answer = "<<1;
        return;
    }
    else if(b == p){
        cout<<"Answer = "<<a;
        return;
    }
    else{
        cout<<a<<"^"<<b<<" MOD "<<p<<"\n";
        int quotient = b / p;
        
        int rem = b % p;
        if (quotient+rem < p){
            cout<<a<<"^"<<(quotient+rem)<<" MOD "<<p<<"\n";
            double result = pow(a, b);
            cout<<"Answer = "<< fmod(result, p)<<"\n";
        }
        else{
           fermats(a, quotient+rem, p); 
        }
    }
    
    
}

int main()
{
    int a, b, p;
    cout<< "enter a^b mod p values: ";
    cin>>a;
    cin>>b;
    cin>>p;
    
    if (!prime(p)){
        cout<<"fermats theorem not applicable";
        return 1;
    }
    else if(gcd(a, p) != 1){
        cout<<"fermats theorem not applicable";
        return 1;
    }
    else{
        cout<<"conditions satisfied for fermats theorem.\n";
        fermats(a, b, p);
    }
    return 0;
}

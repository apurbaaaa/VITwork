#include <iostream>
#include <cmath>
using namespace std;

int extended_euc(int r1, int r2, int s1, int s2, int t1, int t2){
    int q = r1/r2;
    int r = r1 % r2;
    int s = s1 - s2 * q;
    int t = t1 - t2 * q;
    if (r == 0){
        return r2;
    }
    return extended_euc(r2, r, s2, s, r2, t);
    
}

int main(){
    int r1, r2, s1, s2, t1, t2;
    t2, s1 = 1;
    s2, t1 = 0;
    
    
    cout<<"Enter a and b for gcd(a, b): \n";
    cin>> r1>> r2;
    cout<<"gcd("<<r1<<", "<<r2<<")\n";
    int answer = extended_euc(r1, r2, s1, s2, t1, t2);
    cout<<answer;
    
}

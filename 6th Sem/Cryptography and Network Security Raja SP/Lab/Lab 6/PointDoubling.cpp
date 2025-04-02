#include <iostream>
#include <cmath>
using namespace std;
int negcheck(int p, int t2){
    int temp = abs(t2) % p;
    return (p - temp);
}
int inverse(int p, int r1, int r2, int t1, int t2){
    int r = r1 % r2;
    int q = r1/r2;
    int t = t1 - t2 * q;
    if(r2 == 1 && r == 0){
        if(t2<0){
            t2 = negcheck(p, t2);
            return t2;
        }
        else{
            return t2;
        }
    } else{
        return inverse(p, r2, r, t2, t);
    }
}
int main(){
    int p, a, x, y;
    cout<<"Enter p, a, x and y values sequentially:\n";
    cin>>p>>a>>x>>y;
    int up = ((3 * x * x) + a);
    int down = (2*y);
    down = inverse(p, p, down, 0, 1);
    int lambda = (up * down) % p;
    int x3 = (lambda*lambda - x - x) % p;
    int y3 = (negcheck(p, lambda*(x - x3) - y)) % p;
    cout<<"Final Answer: x: "<<x3<<" y: "<< y3<<"\n";
    return 0;

}
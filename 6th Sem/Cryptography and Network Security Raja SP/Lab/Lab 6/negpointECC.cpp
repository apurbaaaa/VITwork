#include <iostream>
#include <cmath>
using namespace std;

int negcheck(int y, int q){
    int temp = y % q;
    return (q - temp);
}

int main(){
    int x, y;
    cout<<"Enter x and y\n";
    cin>>x;
    cin>>y;
    cout<<"Negative point: x, -y % q\n";
    cout<<"Enter q a prime number: \n";
    int q;
    cin>>q;
    y = negcheck(y, q);
    cout<<"Negative point of the given point is: "<<x<<", "<<y;
    return 0;
}
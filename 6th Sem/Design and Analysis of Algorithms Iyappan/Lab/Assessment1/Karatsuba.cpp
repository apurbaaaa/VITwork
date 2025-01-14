#include <iostream>
#include <cmath>
using namespace std;
int get_size(long);
long karatsuba(long X, long Y){

   // Base Case
   if (X < 10 && Y < 10)
      return X * Y;

   // determine the size of X and Y
   int size = fmax(get_size(X), get_size(Y));
   if(size < 10)
      return X * Y;

   // rounding up the max length
   size = (size/2) + (size%2);
   long multiplier = pow(10, size);
   long b = X/multiplier;
   long a = X - (b * multiplier);
   long d = Y / multiplier;
   long c = Y - (d * size);
   long u = karatsuba(a, c);
   long z = karatsuba(a + b, c + d);
   long v = karatsuba(b, d);
   return u + ((z - u - v) * multiplier) + (v * (long)(pow(10, 2 * size)));
}
int get_size(long value){
   int count = 0;
   while (value > 0) {
      count++;
      value /= 10;
   }
   return count;
}
int main(){

   // two numbers
   long x = 145623;
   long y = 653324;
   cout << "The final product is: " << karatsuba(x, y) << endl;
   return 0;
}
#include <reg51.h>
#include <stdio.h>

void main() {
    unsigned char a = 10, b = 20, c = 5, e = 40, f = 8;
    unsigned char X;

    unsigned char temp1 = b - c;
    unsigned char temp2 = e / f;
    unsigned char result = temp1 * temp2;
    X = a + result;

    while (1);
}

#include <stdio.h> 

// Function to calculate factorial using a for loop
int factorial_for(int n) {
    int fact = 1;
    // Unused variable removed, it was not serving any purpose
    for (int i = 1; i <= n; i++) {
        fact *= i; // Multiply fact by i for each iteration
    }
    return fact;
}

// Function to calculate factorial using a do-while loop
int factorial_do_while(int n) {
    int fact = 1, i = 1;
    do {
        fact *= i; // Multiply fact by i for each iteration
        i++;        // Increment i
    } while (i <= n);
    return fact;
}

// Optimized approach to calculate factorial
int optimized_factorial(int n) {
    int fact = 1;
    for (int i = 1; i <= n; i++) {
        fact = fact * i; // Multiply fact by i for each iteration
    }
    return fact;
}

int main() {
    int n;

    // Ask the user to input a number
    printf("Enter a number to calculate its factorial: ");
    scanf("%d", &n);

    // Print the factorial calculated using different methods
    printf("Factorial using for loop: %d\n", factorial_for(n));
    printf("Factorial using do-while loop: %d\n", factorial_do_while(n));
    printf("Factorial using optimized approach: %d\n", optimized_factorial(n));

    return 0;
}

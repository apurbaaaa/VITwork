#include <iostream>
#include <cctype>
#include <cstring>

#define MAX_SYMBOLS 15
#define MAX_LENGTH 100

// Structure to represent a symbol in the symbol table
struct Symbol {
    char symbol[MAX_LENGTH];
    char type[12];
};

int main() {
    int i = 0, j = 0, x = 0, n;
    char b[MAX_LENGTH];
    Symbol symbols[MAX_SYMBOLS];

    std::cout << "Expression terminated by $: ";

    // Input the expression until '$' or max length is reached
    while ((b[i] = getchar()) != '$' && i < MAX_LENGTH - 1) {
        i++;
    }
    b[i] = '\0'; // Null-terminate the input string
    n = i;       // Length of the input string

    std::cout << "Given Expression: " << b << std::endl;
    std::cout << "\nSymbol Table\n";
    std::cout << "Symbol \t Type\n";

    // Parse the input string
    while (j < n) {
        char c = b[j];

        // Check for identifiers (alphabetic characters)
        if (isalpha(c)) {
            int start = j;
            while (j < n && isalpha(b[j])) {
                j++;
            }
            int length = j - start;

            // Copy the identifier into the symbol table
            strncpy(symbols[x].symbol, &b[start], length);
            symbols[x].symbol[length] = '\0';
            strcpy(symbols[x].type, "identifier");
            x++;
        }
        // Check for operators
        else if (c == '+' || c == '-' || c == '*' || c == '=') {
            symbols[x].symbol[0] = c;
            symbols[x].symbol[1] = '\0';
            strcpy(symbols[x].type, "operator");
            x++;
            j++;
        }
        // Skip other characters
        else {
            j++;
        }
    }

    // Print the symbol table
    for (i = 0; i < x; i++) {
        std::cout << symbols[i].symbol << " \t " << symbols[i].type << std::endl;
    }

    return 0;
}

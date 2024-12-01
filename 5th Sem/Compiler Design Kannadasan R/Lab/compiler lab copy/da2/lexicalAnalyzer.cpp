#include <iostream>
#include <cctype>
#include <cstring>

#define MAX_SYMBOLS 100
#define MAX_LENGTH 100

// Structure to represent a lexical token
struct LexicalToken {
    char lexeme[MAX_LENGTH];
    char tokenType[MAX_LENGTH];
};

// Function to add a token to the token array
void addToken(LexicalToken tokens[], int &tokenCount, const char *lexeme, const char *tokenType) {
    strcpy(tokens[tokenCount].lexeme, lexeme);
    strcpy(tokens[tokenCount].tokenType, tokenType);
    tokenCount++;
}

// Function to analyze the input and tokenize it
void analyze(const char *input, LexicalToken tokens[], int &tokenCount) {
    int i = 0;
    while (input[i] != '\0') {
        if (isalpha(input[i])) { // Handle identifiers
            int start = i;
            while (isalnum(input[i])) i++; // Continue until alphanumeric ends
            char lexeme[MAX_LENGTH];
            strncpy(lexeme, &input[start], i - start);
            lexeme[i - start] = '\0';
            addToken(tokens, tokenCount, lexeme, "Identifier");
        } else if (isdigit(input[i])) { // Handle integer literals
            int start = i;
            while (isdigit(input[i])) i++; // Continue until non-digit character
            char lexeme[MAX_LENGTH];
            strncpy(lexeme, &input[start], i - start);
            lexeme[i - start] = '\0';
            addToken(tokens, tokenCount, lexeme, "Integer Literal");
        } else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '=') { // Handle operators
            char lexeme[2] = {input[i], '\0'};
            const char *tokenType = (input[i] == '=') ? "Assignment Operator" : "Operator";
            addToken(tokens, tokenCount, lexeme, tokenType);
            i++;
        } else if (input[i] == ';') { // Handle end of statement
            addToken(tokens, tokenCount, ";", "End of Statement");
            i++;
        } else { // Skip unrecognized characters or spaces
            i++;
        }
    }
}

int main() {
    char input[MAX_LENGTH];
    LexicalToken tokens[MAX_SYMBOLS];
    int tokenCount = 0;

    std::cout << "Enter a C++ expression (terminate with $): ";
    std::cin.getline(input, MAX_LENGTH);

    // Remove the terminating '$' character
    input[strcspn(input, "$")] = '\0';

    // Perform lexical analysis
    analyze(input, tokens, tokenCount);

    // Display the result of the lexical analysis
    std::cout << "\n--- Lexical Analysis Result ---\n";
    std::cout << "Lexeme\t\tToken Type\n";
    std::cout << "-----------------------------\n";
    for (int i = 0; i < tokenCount; i++) {
        std::cout << tokens[i].lexeme << "\t\t" << tokens[i].tokenType << std::endl;
    }

    return 0;
}

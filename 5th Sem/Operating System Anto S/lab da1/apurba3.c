#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isIdentifier(char *str) {
    if (isalpha(str[0])) {
        return 1;
    }
    return 0;
}

int isIntegerLiteral(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=');
}

int isEndOfStatement(char ch) {
    return ch == ';';
}

void analyze(char *input) {
    int i = 0;
    while (input[i] != '\0') {
        if (isalpha(input[i])) {
            printf("'%c' -> Identifier\n", input[i]);
            while (isalnum(input[i+1])) i++;
        } else if (isdigit(input[i])) {
            printf("'%c' -> Integer Literal\n", input[i]);
        } else if (isOperator(input[i])) {
            printf("'%c' -> Operator\n", input[i]);
        } else if (isEndOfStatement(input[i])) {
            printf("'%c' -> End of Statement\n", input[i]);
        }
        i++;
    }
}

int main() {
    char input[] = "Sum=3+2;";

    analyze(input);

    return 0;
}

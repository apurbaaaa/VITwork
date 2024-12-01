#include <iostream>
#include <string>
#include <regex>
#include <algorithm> // For remove()

using namespace std;

int main() {
    string expression;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expression);

    // Regular expression to match numbers and operators
    regex token_regex("(\\d+|[+\\-*/%=])");

    // Remove spaces from the expression
    expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end());

    // Tokenize the expression using regex
    sregex_iterator it(expression.begin(), expression.end(), token_regex), end;

    for (; it != end; ++it) {
        string token = it->str();
        if (isdigit(token[0])) {
            cout << "NUMBER: " << token << endl;
        } else if (token == "=") {
            cout << "EQUALS: " << token << endl;
        } else {
            cout << "OPERATOR: " << token << endl;
        }
    }

    return 0;
}

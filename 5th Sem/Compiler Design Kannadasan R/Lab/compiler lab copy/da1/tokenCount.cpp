#include <iostream>
#include <string>
#include <regex>
#include <algorithm> // For remove()

using namespace std;

int main() {
    string expression;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expression);

    // Define regex for variables, constants, and operators
    regex variable_regex("[a-zA-Z]+");
    regex constant_regex("\\d+");
    regex operator_regex("[+\\-*/%=]");

    int variable_count = 0;
    int constant_count = 0;
    int operator_count = 0;

    // Remove spaces from the expression
    expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end());

    // Count variables
    sregex_iterator it(expression.begin(), expression.end(), variable_regex), end;
    while (it != end) {
        ++variable_count;
        ++it;
    }

    // Count constants
    it = sregex_iterator(expression.begin(), expression.end(), constant_regex);
    while (it != end) {
        ++constant_count;
        ++it;
    }

    // Count operators
    it = sregex_iterator(expression.begin(), expression.end(), operator_regex);
    while (it != end) {
        ++operator_count;
        ++it;
    }

    // Output results
    cout << "Variable count: " << variable_count << endl;
    cout << "Constant count: " << constant_count << endl;
    cout << "Operator count: " << operator_count << endl;

    return 0;
}

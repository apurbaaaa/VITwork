#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include <cctype>

using namespace std;

struct Node {
    int left, right;
    char label;
    char op;
};

vector<Node> dag;
map<char, int> node_map;

void printDAG() {
    cout << "PTR\tLEFT PTR\tRIGHT PTR\tLABEL\tOPERATOR\n";
    for (int i = 0; i < dag.size(); ++i) {
        cout << i << "\t" << dag[i].left << "\t\t" << dag[i].right << "\t\t"
             << dag[i].label << "\t" << dag[i].op << "\n";
    }
}

int main() {
    string expression;
    cout << "Enter the expression: ";
    cin >> expression;

    stack<int> operandStack;
    stack<char> operatorStack;

    for (char ch : expression) {
        if (isalnum(ch)) { // Operand (either number or variable)
            Node node = {-1, -1, ch, '\0'};
            int index = dag.size();
            dag.push_back(node);
            node_map[ch] = index;
            operandStack.push(index);
        }
        else if (ch == '(') { // Left parenthesis
            operatorStack.push(ch);
        }
        else if (ch == ')') { // Right parenthesis
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                char op = operatorStack.top();
                operatorStack.pop();

                int right = operandStack.top();
                operandStack.pop();
                int left = operandStack.top();
                operandStack.pop();

                Node node = {left, right, '\0', op};
                int index = dag.size();
                dag.push_back(node);
                operandStack.push(index);
            }
            operatorStack.pop(); // Pop the '('
        }
        else { // Operator (like +, -, *, /)
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                char op = operatorStack.top();
                operatorStack.pop();

                int right = operandStack.top();
                operandStack.pop();
                int left = operandStack.top();
                operandStack.pop();

                Node node = {left, right, '\0', op};
                int index = dag.size();
                dag.push_back(node);
                operandStack.push(index);
            }
            operatorStack.push(ch);
        }
    }

    // Final processing for remaining operators
    while (!operatorStack.empty()) {
        char op = operatorStack.top();
        operatorStack.pop();

        int right = operandStack.top();
        operandStack.pop();
        int left = operandStack.top();
        operandStack.pop();

        Node node = {left, right, '\0', op};
        int index = dag.size();
        dag.push_back(node);
        operandStack.push(index);
    }

    printDAG();

    return 0;
}

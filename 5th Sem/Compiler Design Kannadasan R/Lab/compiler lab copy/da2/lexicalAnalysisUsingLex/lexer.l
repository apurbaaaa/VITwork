%{
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int inCommentBlock = 0;
%}

identifier  [a-zA-Z][a-zA-Z0-9]*

%%
"#.*" {
    cout << "\n" << yytext << " is a Preprocessor Directive";
}

int|float|main|if|else|printf|scanf|for|char|getch|while {
    cout << "\n" << yytext << " is a Keyword";
}

"/*" {
    inCommentBlock = 1;
}

"*/" {
    inCommentBlock = 0;
}

{identifier}\( {
    if (!inCommentBlock)
        cout << "\nFunction:\t" << yytext;
}

"{" {
    if (!inCommentBlock)
        cout << "\nBlock Begins";
}

"}" {
    if (!inCommentBlock)
        cout << "\nBlock Ends";
}

{identifier}(\[[0-9]*\])? {
    if (!inCommentBlock)
        cout << "\n" << yytext << " is an Identifier";
}

\".*\" {
    if (!inCommentBlock)
        cout << "\n" << yytext << " is a String";
}

[0-9]+ {
    if (!inCommentBlock)
        cout << "\n" << yytext << " is a Number";
}

\)(\;)? {
    if (!inCommentBlock) {
        cout << "\t" << yytext << "\n";
    }
}

\( {
    cout << yytext;
}

"=" {
    if (!inCommentBlock)
        cout << "\n" << yytext << " is an Assignment Operator";
}

"<="|">="|"<"|"=="|">" {
    if (!inCommentBlock)
        cout << "\n" << yytext << " is a Relational Operator";
}

.|\n {
    // Do nothing for unrecognized characters
}
%%

int main(int argc, char **argv) {
    if (argc > 1) {
        ifstream file(argv[1]);
        if (!file.is_open()) {
            cerr << "\nCould not open the file: " << argv[1] << endl;
            exit(1);
        }
        yyin = fopen(argv[1], "r");
    }

    yylex();
    cout << "\n\n";
    return 0;
}

int yywrap() {
    return 1;
}

%{
#include <stdio.h>
#include <stdlib.h>
%}
%token ALPHA NUMBER ENTER ER
%%
var: v ENTER {
    printf("Valid Variable\n");
    exit(0);
}
v: ALPHA exp1
exp1: ALPHA exp1
    | NUMBER exp1
    | /* empty */
%%
void yyerror(const char *s) { // Explicit return type and parameter
    printf("Invalid Variable: %s\n", s);
}

int main() {
    printf("Enter the expression: ");
    yyparse();
    return 0; // Ensure main returns an int
}

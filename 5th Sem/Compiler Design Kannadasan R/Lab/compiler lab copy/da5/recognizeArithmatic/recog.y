%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void yyerror(const char *s);
int yylex(void);

%}

%union {
    int num;
    char *var;
}

%token <num> NUMBER
%token <var> VARIABLE

%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

%%

S: VARIABLE '=' E {
    printf("\nEntered arithmetic expression is Valid\n\n");
}
;

E: E '+' E
  | E '-' E
  | E '*' E
  | E '/' E
  | E '%' E
  | '(' E ')'
  | NUMBER
  | VARIABLE
  ;

%%

int main() {
    printf("\nEnter Any Arithmetic Expression which can have operations Addition, Subtraction, Multiplication, Division, Modulus and Round brackets:\n");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    printf("\nEntered arithmetic expression is Invalid: %s\n\n", s);
}

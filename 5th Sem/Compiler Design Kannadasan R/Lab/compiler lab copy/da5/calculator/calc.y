%{
#include <stdio.h>
#include <stdlib.h> // Required for atoi
int flag = 0;
%}

%token NUMBER
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'


%%
ArithmeticExpression:
    E {
        printf("\nResult = %d\n", $1);
        return 0;
    }
;

E:
    E '+' E { $$ = $1 + $3; }
    | E '-' E { $$ = $1 - $3; }
    | E '*' E { $$ = $1 * $3; }
    | E '/' E { $$ = $1 / $3; }
    | E '%' E { $$ = $1 % $3; }
    | '(' E ')' { $$ = $2; }
    | NUMBER { $$ = $1; }
;

%%

int main() {
    printf("Enter any arithmetic expression (Addition, Subtraction, Multiplication, Division, Modulus, and Round brackets are supported):\n");
    yyparse();
    if (flag == 0)
        printf("\nEntered arithmetic expression is Valid\n\n");
    return 0;
}

void yyerror(const char *msg) {
    printf("\nError: %s\n", msg);
    flag = 1;
}

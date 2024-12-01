%{
#include <stdio.h>
#include <ctype.h>
#define YYSTYPE char
int f=0;
%}
%token id err
%left '-' '+'
%left '*' '/'
%%
input: /* empty string */
     | input exp {}
     | error {f=1;}
   ;
exp: exp '+' exp { printf("+"); }
     | exp '-' exp { printf("-"); }
     | exp '*' exp { printf("*"); }
     | exp '/' exp { printf("/");}
     | id { printf("%c",yylval); }
   ;
%%
int main()
{
   printf("\nEnter an arithmetic expression:\n\n");
   yyparse();
   printf("\n");
   if(f==1)
     printf("Invalid Expression\n");
   return 0;
}
int yywrap()
{
   return 1;
}
int yyerror(char *mes) {
   return 0;
}
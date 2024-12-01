%{
#include <stdio.h>
#include "y.tab.h"
extern YYSTYPE yylval;
%}

%%
[a-zA-Z]+    { yylval.var = strdup(yytext); return VARIABLE; }
[0-9]+       { yylval.num = atoi(yytext); return NUMBER; }
[\t]         ; // ignore tabs
[\n]         { return 0; } // newline (end of input)
.            { return yytext[0]; } // return any other character as is
%%

int yywrap() {
    return 1;
}

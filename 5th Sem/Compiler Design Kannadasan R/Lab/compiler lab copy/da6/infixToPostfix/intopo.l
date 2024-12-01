%{
#include <stdio.h>
#include "y.tab.h"
extern int yylval; 
%}
op "+"|"-"|"*"|"/"
%%
[a-z] { yylval=*yytext; return id; }
{op} { return (int) yytext[0]; }
\n { return(0); }
. { return err; }
%%
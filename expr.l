%option noyywrap
%{
#include "y.tab.h"
%}

%%
[a-zA-Z][a-zA-Z0-9]* { return ID; }
[0-9]+               { return NUM; }
[+\-*/]              { return yytext[0]; }
[ \t]                ;
\n                    { return '\n'; }
.                    { return yytext[0]; }
%%

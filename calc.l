%{
#include "calc.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[+\-*/()]   { return yytext[0]; }
\n          { return 0; }
[ \t]       ;   // ignore spaces
.           { return yytext[0]; }

%%

int yywrap() {
    return 1;
}

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "y.tab.h"
%}

%%

[a-zA-Z]+      { yylval.str = strdup(yytext); return ID; }
[0-9]+         { yylval.str = strdup(yytext); return NUM; }

"+"            { return '+'; }
"-"            { return '-'; }
"*"            { return '*'; }
"/"            { return '/'; }
"="            { return '='; }
";"            { return ';'; }
"("            { return '('; }
")"            { return ')'; }

[ \t\n]+       ;   // ignore whitespace

.              { return yytext[0]; }

%%

int yywrap() {
    return 1;
}

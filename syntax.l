%{
#include "syntax.tab.h"
#include <string.h>
#include <stdlib.h>
%}

%%

[0-9]+ {
    yylval.str = strdup(yytext);
    return NUM;
}

[a-zA-Z]+ {
    yylval.str = strdup(yytext);
    return ID;
}

[ \t]   ;

\n      return '\n';

"+" return '+';
"-" return '-';
"*" return '*';
"/" return '/';
"(" return '(';
")" return ')';

. return yytext[0];

%%

int yywrap() {
    return 1;
}

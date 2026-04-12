%{
#include "lalr.tab.h"
%}

%%
c { return C_TOKEN; }
d { return D_TOKEN; }
\n { return 0; }
[ \t] ;
. { return yytext[0]; }
%%

int yywrap() {
 return 1;
}

%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
int yyerror(const char *s);
%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%right UMINUS

%%

S : E { printf("Result = %d\n", $1); }
  ;

E : E '+' E   { $$ = $1 + $3; }
  | E '-' E   { $$ = $1 - $3; }
  | E '*' E   { $$ = $1 * $3; }
  | E '/' E   { $$ = $1 / $3; }
  | '(' E ')' { $$ = $2; }
  | '-' E %prec UMINUS { $$ = -$2; }
  | NUMBER    { $$ = $1; }
  ;

%%

int main() {
    printf("Enter expression:\n");
    yyparse();
    return 0;
}

int yyerror(const char *s) {
    printf("Invalid Expression\n");
    return 0;
}

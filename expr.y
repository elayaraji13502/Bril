%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
int yyerror(char *s);
%}

%token NUM ID
%left '+' '-'
%left '*' '/'

%%
start:
      expr '\n'   { printf("Valid arithmetic expression\n"); }
     ;

expr:
      expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | ID
    | NUM
    ;
%%
int main() {
    printf("Enter arithmetic expression: ");
    yyparse();
    return 0;
}

int yyerror(char *s) {
    printf("Invalid arithmetic expression\n");
    exit(0);
}

{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
int yyerror(char *s);
%}

%token LETTER DIGIT

%%
start:
      variable '\n'   { printf("Valid variable name\n"); }
     ;

variable:
      LETTER
    | variable LETTER
    | variable DIGIT
    ;
%%
int main() {
    printf("Enter variable name: ");
    yyparse();
    return 0;
}

int yyerror(char *s) {
    printf("Invalid variable name\n");
    exit(0);
}

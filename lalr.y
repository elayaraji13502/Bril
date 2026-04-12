%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();
%}

%token C_TOKEN D_TOKEN

%%

S : C C
 ;

C : C_TOKEN C
  | D_TOKEN
 ;

%%

int main() {
 printf("Enter string:\n");
 yyparse();
 return 0;
}

void yyerror(const char *s) {
 printf("Invalid string\n");
}

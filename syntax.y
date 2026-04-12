%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

node* root;

node* createNode(char *val, node *l, node *r) {
    node *newNode = (node*)malloc(sizeof(node));
    strcpy(newNode->value, val);
    newNode->left = l;
    newNode->right = r;
    return newNode;
}

void printPrefix(node* root) {
    if (!root) return;
    printf("%s ", root->value);
    printPrefix(root->left);
    printPrefix(root->right);
}

void printTree(node* root, int space) {
    if (!root) return;

    space += 5;
    printTree(root->right, space);

    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");
    printf("%s\n", root->value);

    printTree(root->left, space);
}

int yylex();
void yyerror(const char *s);
%}

/* 🔥 Important Fix */
%code requires {
    #include "ast.h"
}

%union {
    char* str;
    node* nd;
}

%token <str> ID NUM
%token '\n'
%type <nd> E T F

%left '+' '-'
%left '*' '/'

%%

input:
    E '\n' {
        root = $1;

        printf("\nPrefix:\n");
        printPrefix(root);

        printf("\n\nTree:\n");
        printTree(root, 0);
        printf("\n");

        return 0;
    }
;

E:
    E '+' T { $$ = createNode("+", $1, $3); }
  | E '-' T { $$ = createNode("-", $1, $3); }
  | T       { $$ = $1; }
;

T:
    T '*' F { $$ = createNode("*", $1, $3); }
  | T '/' F { $$ = createNode("/", $1, $3); }
  | F       { $$ = $1; }
;

F:
    ID  { $$ = createNode($1, NULL, NULL); }
  | NUM { $$ = createNode($1, NULL, NULL); }
  | '(' E ')' { $$ = $2; }
;

%%

int main() {
    printf("Enter Expression:\n");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    printf("Invalid Expression\n");
}

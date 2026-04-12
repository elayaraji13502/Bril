#ifndef AST_H
#define AST_H

typedef struct node {
    char value[20];
    struct node *left, *right;
} node;

#endif

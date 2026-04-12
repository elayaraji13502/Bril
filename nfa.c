#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isIdentifier(char str[]) {
    int i = 0;

    if (isalpha(str[i]) || str[i] == '_') {
        i++;
        while (isalnum(str[i]) || str[i] == '_')
            i++;
        return (str[i] == '\0');
    }
    return 0;
}
int isConstant(char str[]) {
    int i = 0;

    if (isdigit(str[i])) {
        i++;
        while (isdigit(str[i]))
            i++;
        return (str[i] == '\0');
    }
    return 0;
}

int isOperator(char str[]) {
    if (strlen(str) == 1) {
        switch (str[0]) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '=':
            case '<':
            case '>':
                return 1;
        }
    }
    return 0;
}
int isEpsilon(char str[]) {
    return (strlen(str) == 0 || strcmp(str, "()") == 0);
}
int main() {
    char input[50];
    printf("Enter a string : ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';

    if (isEpsilon(input))
        printf("Token: EPSILON(Special token)\n");
    else if (isIdentifier(input))
        printf("Token: IDENTIFIER\n");
    else if (isConstant(input))
        printf("Token: CONSTANT\n");
    else if (isOperator(input))
        printf("Token: OPERATOR\n");
    else
        printf("Invalid Token\n");

    return 0;
}

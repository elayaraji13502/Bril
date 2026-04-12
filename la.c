#include <stdio.h>
#include <ctype.h>
#include <string.h>

char keywords[][10] = {"int", "float", "if", "else", "while", "return"};

int isKeyword(char word[]) {
    for (int i = 0; i < 6; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    char input[100], token[50];
    int i = 0, j = 0;

    printf("Enter a statement: ");
    fgets(input, sizeof(input), stdin);

    // Remove newline character added by fgets
    input[strcspn(input, "\n")] = '\0';

    while (input[i] != '\0') {

        // IDENTIFIER or KEYWORD
        if (isalpha(input[i])) {
            j = 0;
            while (isalnum(input[i])) {
                token[j++] = input[i++];
            }
            token[j] = '\0';

            if (isKeyword(token))
                printf("%s : Keyword\n", token);
            else
                printf("%s : Identifier\n", token);
        }

        // NUMBER
        else if (isdigit(input[i])) {
            j = 0;
            while (isdigit(input[i])) {
                token[j++] = input[i++];
            }
            token[j] = '\0';
            printf("%s : Number\n", token);
        }

        // OPERATOR
        else if (strchr("+-*/=<>", input[i])) {
            printf("%c : Operator\n", input[i]);
            i++;
        }

        // SPECIAL SYMBOL
        else if (strchr(";,(){}", input[i])) {
            printf("%c : Special Symbol\n", input[i]);
            i++;
        }

        // IGNORE SPACES / UNKNOWN
        else {
            i++;
        }
    }

    return 0;
}

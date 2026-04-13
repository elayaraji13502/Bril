#include <stdio.h>
#include <string.h>

#define MAX 100

char tac[MAX][50];
int n;

/* Generate 8086 Assembly */
void generateAssembly() {
    char op, arg1[10], arg2[10], res[10];

    printf("\n========== 8086 ASSEMBLY ==========\n\n");

    for (int i = 0; i < n; i++) {

        // 🔹 Print label FIRST
        printf("L%d:\n", i + 1);

        /* Assignment: a = b */
        if (sscanf(tac[i], "%s = %s", res, arg1) == 2 &&
            !strchr(tac[i], '+') && !strchr(tac[i], '-') &&
            !strchr(tac[i], '*') && !strchr(tac[i], '/')) {

            printf("    MOV AX, %s\n", arg1);
            printf("    MOV %s, AX\n\n", res);
        }

        /* Arithmetic: t1 = a + b */
        else if (sscanf(tac[i], "%s = %s %c %s", res, arg1, &op, arg2) == 4) {

            printf("    MOV AX, %s\n", arg1);

            switch (op) {
                case '+':
                    printf("    ADD AX, %s\n", arg2);
                    break;
                case '-':
                    printf("    SUB AX, %s\n", arg2);
                    break;
                case '*':
                    printf("    MOV BX, %s\n", arg2);
                    printf("    MUL BX\n");
                    break;
                case '/':
                    printf("    MOV BX, %s\n", arg2);
                    printf("    DIV BX\n");
                    break;
            }

            printf("    MOV %s, AX\n\n", res);
        }

        /* IF condition (generic) */
        else if (strstr(tac[i], "if")) {
            int label;
            char relop[3];

            sscanf(tac[i], "if %s %s %s goto %d", arg1, relop, arg2, &label);

            printf("    MOV AX, %s\n", arg1);
            printf("    CMP AX, %s\n", arg2);

            if (strcmp(relop, ">") == 0)
                printf("    JG L%d\n\n", label);
            else if (strcmp(relop, "<") == 0)
                printf("    JL L%d\n\n", label);
            else if (strcmp(relop, "==") == 0)
                printf("    JE L%d\n\n", label);
            else if (strcmp(relop, "!=") == 0)
                printf("    JNE L%d\n\n", label);
            else if (strcmp(relop, ">=") == 0)
                printf("    JGE L%d\n\n", label);
            else if (strcmp(relop, "<=") == 0)
                printf("    JLE L%d\n\n", label);
        }

        /* GOTO */
        else if (strstr(tac[i], "goto")) {
            int label;
            sscanf(tac[i], "goto %d", &label);
            printf("    JMP L%d\n\n", label);
        }

        /* RETURN */
        else if (strstr(tac[i], "return")) {
            sscanf(tac[i], "return %s", arg1);
            printf("    MOV AX, %s\n", arg1);
            printf("    RET\n\n");
        }

        else {
            printf("    ; Unsupported statement\n\n");
        }
    }

    printf("====================================\n");
}

int main() {
    printf("Enter number of TAC statements: ");
    scanf("%d", &n);
    getchar();

    printf("Enter TAC statements:\n");

    for (int i = 0; i < n; i++) {
        fgets(tac[i], sizeof(tac[i]), stdin);
        tac[i][strcspn(tac[i], "\n")] = '\0';
    }

    generateAssembly();

    return 0;

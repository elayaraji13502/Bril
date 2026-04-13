#include <stdio.h>
#include <string.h>

#define MAX 100

char tac[MAX][50];
int leader[MAX];
int n;

/* Check if statement contains jump */
int isJump(char *stmt) {
    return (strstr(stmt, "goto") != NULL);
}

/* Extract target line number */
int getTarget(char *stmt) {
    int target;
    char *pos = strstr(stmt, "goto");

    if (pos != NULL) {
        sscanf(pos, "goto %d", &target);
        return target;
    }
    return -1;
}

/* Find leaders */
void findLeaders() {
    for(int i = 0; i < n; i++)
        leader[i] = 0;

    leader[0] = 1; // First statement

    for (int i = 0; i < n; i++) {

        if (isJump(tac[i])) {

            int target = getTarget(tac[i]);

            // Target of jump is leader
            if (target > 0 && target <= n)
                leader[target - 1] = 1;

            // Next statement is also leader
            if (i + 1 < n)
                leader[i + 1] = 1;
        }
    }
}

/* Print basic blocks */
void printBlocks() {
    int block = 1;

    printf("\n========== BASIC BLOCKS ==========\n");

    for (int i = 0; i < n; i++) {
        if (leader[i]) {
            printf("\nBlock %d:\n", block++);
        }
        printf("%d: %s\n", i + 1, tac[i]);
    }
}

/* Construct flow graph */
void flowGraph() {
    printf("\n========== FLOW GRAPH ==========\n");

    for (int i = 0; i < n; i++) {

        if (strstr(tac[i], "if")) {
            int target = getTarget(tac[i]);

            printf("Node %d -> Node %d (True)\n", i + 1, target);
            if (i + 1 < n)
                printf("Node %d -> Node %d (False)\n", i + 1, i + 2);
        }

        else if (strstr(tac[i], "goto")) {
            int target = getTarget(tac[i]);
            printf("Node %d -> Node %d\n", i + 1, target);
        }

        else {
            if (i + 1 < n)
                printf("Node %d -> Node %d\n", i + 1, i + 2);
        }
    }
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

    findLeaders();
    printBlocks();
    flowGraph();

    return 0;
}

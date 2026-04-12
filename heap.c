#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 10

int memory[MEMORY_SIZE];
int SP = -1;
int HP = MEMORY_SIZE;

void display_stack() {
    printf("\n--- STACK LAYOUT ---\n");

    if (SP < 0) {
        printf("Stack is Empty\n");
    } else {
        for (int i = SP; i >= 0; i--) {
            printf("Index %d : %d", i, memory[i]);

            if (i == SP)
                printf(" <-- SP");

            printf("\n");
        }
    }

    printf("--------------------\n");
}

void display_full_memory() {
    printf("\n===== FULL MEMORY LAYOUT =====\n");
    printf("SP = %d | HP = %d\n\n", SP, HP);

    for (int i = 0; i < MEMORY_SIZE; i++) {
        printf("Index %d : %d", i, memory[i]);

        if (i == SP)
            printf(" <-- SP");

        if (i <= SP)
            printf(" [STACK]");
        else if (i >= HP)
            printf(" [HEAP]");
        else
            printf(" [FREE]");

        printf("\n");
    }

    printf("================================\n");
}

void push(int value, char *info) {
    if (SP + 1 >= HP) {
        printf("ERROR: Stack-Heap Collision!\n");
        return;
    }

    SP++;
    memory[SP] = value;

    printf("\nPUSH (%s) = %d\n", info, value);
    display_stack();
}

void pop(char *info) {
    if (SP < 0) {
        printf("ERROR: Stack Underflow!\n");
        return;
    }

    int val = memory[SP];

    printf("\nPOP (%s) = %d\n", info, val);

    memory[SP] = 0;
    SP--;

    display_stack();
}

void simulate_function(int maxDepth, int currentLevel) {

    printf("\n=== FUNCTION CALL : Level %d ===\n", currentLevel);

    push(100 + currentLevel, "Return Address");
    push(currentLevel, "Parameter");
    push(currentLevel * 10, "Local Variable");

    printf("\nFull Memory After Activation Record Creation (Level %d)\n", currentLevel);
    display_full_memory();

    if (currentLevel < maxDepth) {
        simulate_function(maxDepth, currentLevel + 1);
    }

    printf("\nPreparing to return from Level %d\n", currentLevel);

    pop("Local Variable");
    pop("Parameter");
    pop("Return Address");

    printf("\nFull Memory After Activation Record Removal (Level %d)\n", currentLevel);
    display_full_memory();

    printf("=== FUNCTION RETURN : Level %d ===\n", currentLevel);
}

void heap_alloc(int size) {

    if (HP - size <= SP) {
        printf("ERROR: Heap Overflow (Collision)!\n");
        return;
    }

    HP -= size;

    printf("Allocated %d heap cells starting at index %d\n", size, HP);
}

void heap_free(int size) {

    if (HP + size > MEMORY_SIZE) {
        printf("ERROR: Invalid Free!\n");
        return;
    }

    HP += size;

    printf("Freed %d heap cells\n", size);
}

int main() {

    memset(memory, 0, sizeof(memory));

    int choice, size, depth;

    while (1) {

        printf("\n====== RUNTIME SIMULATOR ======\n");
        printf("1. Heap Allocate\n");
        printf("2. Heap Free\n");
        printf("3. Simulate Function Call (with Depth)\n");
        printf("4. Display Full Memory\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("Enter heap size to allocate: ");
            scanf("%d", &size);

            heap_alloc(size);
            display_full_memory();
            break;

        case 2:
            printf("Enter heap size to free: ");
            scanf("%d", &size);

            heap_free(size);
            display_full_memory();
            break;

        case 3:
            printf("Enter recursion depth: ");
            scanf("%d", &depth);

            if (depth <= 0) {
                printf("Invalid depth!\n");
                break;
            }

            simulate_function(depth, 1);
            break;

        case 4:
            display_full_memory();
            break;

        case 5:
            printf("Exiting Program...\n");
            exit(0);

        default:
            printf("Invalid Choice!\n");
        }
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Symbol {
    char name[50];
    char type[20];
    int value;
    struct Symbol *next;
};

struct Symbol *head = NULL;

void insert() {
    struct Symbol *newNode = (struct Symbol*)malloc(sizeof(struct Symbol));

    printf("Enter name: ");
    scanf("%s", newNode->name);

    printf("Enter type: ");
    scanf("%s", newNode->type);

    printf("Enter value: ");
    scanf("%d", &newNode->value);

    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        struct Symbol *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    printf("Symbol inserted successfully!\n");
}

void deleteSymbol() {
    char name[50];
    printf("Enter name to delete: ");
    scanf("%s", name);

    struct Symbol *temp = head, *prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            if (prev == NULL) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Symbol deleted successfully!\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("Symbol not found!\n");
}

void display() {
    struct Symbol *temp = head;

    if (temp == NULL) {
        printf("Symbol table is empty!\n");
        return;
    }

    printf("\nSymbol Table:\n");
    printf("Name\tType\tValue\n");

    while (temp != NULL) {
        printf("%s\t%s\t%d\n",
               temp->name,
               temp->type,
               temp->value);
        temp = temp->next;
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Symbol Table Menu ---\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insert();
                break;
            case 2:
                deleteSymbol();
                break;
            case 3:
                display();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

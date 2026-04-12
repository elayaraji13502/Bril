#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAX 10

char production[MAX][10];
int n;

// ---------- FIRST ----------
void findFirst(char c){
    int i;

    // If terminal
    if(!isupper(c)){
        printf("%c ", c);
        return;
    }

    for(i = 0; i < n; i++){
        if(production[i][0] == c){

            // If epsilon
            if(production[i][2] == '#'){
                printf("# ");
            }

            // If terminal
            else if(!isupper(production[i][2])){
                printf("%c ", production[i][2]);
            }

            // If non-terminal
            else{
                findFirst(production[i][2]);
            }
        }
    }
}

// ---------- FOLLOW ----------
void findFollow(char c){
    int i, j;

    // Start symbol
    if(production[0][0] == c){
        printf("$ ");
    }

    for(i = 0; i < n; i++){
        for(j = 2; j < strlen(production[i]); j++){

            if(production[i][j] == c){

                // If next symbol exists
                if(production[i][j+1] != '\0'){
                    findFirst(production[i][j+1]);
                }

                // If at end
                if(production[i][j+1] == '\0' && c != production[i][0]){
                    findFollow(production[i][0]);
                }
            }
        }
    }
}

// ---------- MAIN ----------
int main(){

    int i;
    char stack[50], input[50];
    int top = -1, ip = 0;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (Example: E=TE):\n");

    for(i = 0; i < n; i++){
        scanf("%s", production[i]);
    }

    // FIRST
    printf("\nFIRST Sets\n");
    for(i = 0; i < n; i++){
        printf("FIRST(%c) = { ", production[i][0]);
        findFirst(production[i][0]);
        printf("}\n");
    }

    // FOLLOW
    printf("\nFOLLOW Sets\n");
    for(i = 0; i < n; i++){
        printf("FOLLOW(%c) = { ", production[i][0]);
        findFollow(production[i][0]);
        printf("}\n");
    }

    // LL(1) Table (Hardcoded Example)
    printf("\nLL(1) Parsing Table\n");
    printf("\n\t i\t +\t $\n");
    printf("E\t E->TE'\t -\t -\n");
    printf("E'\t -\t E'->+TE'\t E'->e\n");
    printf("T\t T->i\t -\t -\n");

    // Input
    printf("\nEnter input string (end with $): ");
    scanf("%s", input);

    // Initialize stack
    stack[++top] = '$';
    stack[++top] = production[0][0];

    printf("\nStack\tInput\tAction\n");

    while(top != -1){

        // Print stack
        for(i = top; i >= 0; i--)
            printf("%c", stack[i]);

        printf("\t%s\t", input + ip);

        // Match
        if(stack[top] == input[ip]){
            printf("Match %c\n", input[ip]);
            top--;
            ip++;
        }

        // E -> TE'
        else if(stack[top] == 'E'){
            printf("E->TE'\n");
            top--;
            stack[++top] = 'X'; // E'
            stack[++top] = 'T';
        }

        // E' -> +TE' | e
        else if(stack[top] == 'X'){
            if(input[ip] == '+'){
                printf("E'->+TE'\n");
                top--;
                stack[++top] = 'X';
                stack[++top] = 'T';
                stack[++top] = '+';
            } else {
                printf("E'->e\n");
                top--;
            }
        }

        // T -> i
        else if(stack[top] == 'T'){
            printf("T->i\n");
            top--;
            stack[++top] = 'i';
        }

        else{
            printf("Error\n");
            break;
        }

        // Accept condition
        if(stack[top] == '$' && input[ip] == '$'){
            printf("$\t$\tAccept\n");
            break;
        }
    }

    return 0;
}

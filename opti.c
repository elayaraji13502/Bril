#include <stdio.h>

int main() {
    int a, b, n, x;
    printf("=== CODE OPTIMIZATION ===\n");

    printf("Enter two constants a and b for constant folding (a+b): ");
    scanf("%d %d", &a, &b);
    int c = a + b;
    printf("Constant Folding: %d + %d = %d\n", a, b, c);

    printf("Enter loop count for strength reduction: ");
    scanf("%d", &n);
    int sum = 0;
    for(int i = 0; i < n; i++) {
        sum += i + i;
    }
    printf("Strength Reduction (i*2 replaced with i+i), sum = %d\n", sum);

    printf("Enter value for x (for z = x*1 + 0 simplified): ");
    scanf("%d", &x);
    int z = x; 
    printf("Algebraic Transformation: z = %d\n", z);

    return 0;
}

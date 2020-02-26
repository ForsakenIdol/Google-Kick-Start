#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// To compile: gcc solution.c -pthread -lm -O3 -Werror -o solution

int main(int argc, char** argv) {
    int T; // Number of test cases
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        int N, K, x1, y1, C, D, E1, E2, F;
        scanf("%d %d %d %d %d %d %d %d %d", &N, &K, &x1, &y1, &C, &D, &E1, &E2, &F);
        printf("Input values: N: %d K: %d x1: %d y1: %d C: %d D: %d E1: %d E2: %d F: %d\n", N, K, x1, y1, C, D, E1, E2, F); // Debug print
        // TODO
        int A[N];
    }
    return 0;
}
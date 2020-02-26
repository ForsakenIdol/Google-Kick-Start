#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// To compile: gcc solution.c -pthread -lm -O3 -Werror -o solution


/*
 *  Calculates the ith exponential power of the array arr with array length N.
 */
int exponential_power(int i, int arr[], int N) {
    int power = 0;

    return power;
}

/*
 *  Prints the array arr with array length N to console.
 *  This is a debug method! Do NOT call this in the final submission code
 */
void print_array(int A[], int N) {
    printf("[%d, " , A[0]);
        for (int i = 1; i < N - 1; i++) printf("%d, " , A[i]);
        printf("%d]" , A[N - 1]);
}

int main(int argc, char** argv) {
    int T; // Number of test cases
    scanf("%d", &T);
    for (int z = 1; z <= T; z++) {
        int N, K, x1, y1, C, D, E1, E2, F;
        scanf("%d %d %d %d %d %d %d %d %d", &N, &K, &x1, &y1, &C, &D, &E1, &E2, &F);
        printf("Input values: N: %d K: %d x1: %d y1: %d C: %d D: %d E1: %d E2: %d F: %d\n", N, K, x1, y1, C, D, E1, E2, F); // Debug print
        
        int A[N];
        A[0] = (x1 + y1) % F;
        int xn1 = x1; int yn1 = y1;
        for (int i = 1; i < N; i++) {
            int xn = (C * xn1 + D * yn1 + E1) % F;
            int yn = (D * xn1 + C * yn1 + E2) % F;
            xn1 = xn; yn1 = yn;
            A[i] = (xn + yn) % F;
        }
        print_array(A, N);

        // TODO - Calculate exponential power

    }
    return 0;
}
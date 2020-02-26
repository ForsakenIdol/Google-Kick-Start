#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// To compile: gcc solution.c -pthread -lm -O3 -Werror -o solution

/*
 *  Prints the array arr with array length N to console.
 *  This is a debug method! Do NOT call this in the final submission code
 */
void print_array(long A[], int N) {
    printf("[%ld, " , A[0]);
        for (int i = 1; i < N - 1; i++) printf("%ld, " , A[i]);
        printf("%ld]\n" , A[N - 1]);
}

/*
 *  Calculates the ith exponential power of the array A with array length N.
 */
long exponential_power(int i, long A[], int N) {
    long power = 0;
    for (int x = 0; x < N; x++) {
        for (int y = x; y < N; y++) {
            for (int z = x; z <= y; z++) {
                power += A[z] * pow(z - x + 1, i);
            }
        }
    }
    return power;
}

// Calculate the total sum of K exponential powers on array A with array length K.
long total_exponential_power(int K, long A[], int N) {
    long result = 0;
    for (int i = 1; i <= K; i++) result += exponential_power(i, A, N);
    return result;
}

int main(int argc, char** argv) {
    int T; // Number of test cases
    scanf("%d", &T);
    for (int z = 1; z <= T; z++) {
        int N, K, x1, y1, C, D, E1, E2, F;
        scanf("%d %d %d %d %d %d %d %d %d", &N, &K, &x1, &y1, &C, &D, &E1, &E2, &F);

        long* A = calloc(N, sizeof(long));
        A[0] = (x1 + y1) % F;
        long xn1 = x1; long yn1 = y1;
        for (int i = 1; i < N; i++) {
            long xn = (C * xn1 + D * yn1 + E1) % F;
            long yn = (D * xn1 + C * yn1 + E2) % F;
            xn1 = xn; yn1 = yn;
            A[i] = (xn + yn) % F;
        }

        long result = total_exponential_power(K, A, N) % 1000000007;
        printf("Case #%d: %ld\n", z, result);

        free(A);

    }
    return 0;
}
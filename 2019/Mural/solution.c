#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// To compile: gcc solution.c -pthread -lm -O3 -Werror -o solution

int main(int argc, char** argv) {
    int T; // Number of test sets
    scanf("%d", &T);
    for (int z = 0; z < T; z++) {
        int N; // 'N' is the number of sections in the "wall"
        scanf("%d", &N);
        char w[N];
        scanf("%s", w);

        // Convert char array to ints
        int wall[N];
        for (int i = 0; i < N; i++) {
            // We convert the string value to an int by 1. Raw casting, and 2. Subtracting the ASCII value of the '0' offset.
            wall[i] = (int) w[i];
            wall[i] -= '0';
        }

        // Beauty value checking routine
        int muralLength = N / 2;
        if (N % 2 == 1) muralLength++;
        int maxBeauty = 0;
        for (int i = 0; i < muralLength; i++) maxBeauty += wall[(N - 1) - i];
        int newBeauty = maxBeauty;
        // Keep a rolling total, this is important so we don't always recalculate the beauty value for large walls
        for (int i = (N - 1) - muralLength; i >= 0; i--) {
            // Update new total
            newBeauty -= wall[i + muralLength];
            newBeauty += wall[i];
            // Check new total and update if larger total exists
            if (newBeauty > maxBeauty) maxBeauty = newBeauty;
        }
        fprintf(stdout, "Case #%d: %d\n", z + 1, maxBeauty);

    }
    return 0;
}
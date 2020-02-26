#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*
 * ------- Code Questions -------
 * - Why does `char response[32]` compare correctly after being loaded from stdin, but not `char* response`?
 * - I don't understand why my header `for (int test = 0; test < N || !done; test++)` doesn't work.
 *      - In the same vein, I don't understand what is meant by the correct header `for (++A; !done;)`.
 */

int main(int argc, char** argv) {
    int T; // Number of test cases to process
    scanf("%d", &T);

    for (int i = 0; i < T; i++) {
        int A; /* Lower bound, excluded */ int B; // Upper bound, included
        fscanf(stdin, "%d %d", &A, &B);
        int N; // Maximum number of allowed guesses
        fscanf(stdin, "%d", &N);
        bool done = false; // Signals to move on to the next test case

        // Searching Algorithm
        // for (int test = 0; test < N || !done; test++) {
        for (++A; !done;) {
            int mid = (A + B) / 2;
            fprintf(stdout, "%d\n", mid);
            fflush(stdout); // Flush the stdout buffer, causing the output to appear IMMEDIATELY

            char response[32]; // The response from the judge
            fscanf(stdin, "%s", response); // Note the lack of dereferencing for character array inputs from stdin
            if (!strcmp(response, "CORRECT")) done = true;
            // Note in the small and big comparisons, we no longer include the "mid" value in the next binary search iteration.
            else if (!strcmp(response, "TOO_SMALL")) /* Check upper half */ A = mid + 1;
            else if (!strcmp(response, "TOO_BIG")) /* Check lower half */ B = mid - 1;
            else /* WRONG_ANSWER or other received, something went wrong! */ {
                fprintf(stderr, "WRONG_ANSWER received!\n");
                return 1;
            }
        }
    }
    return 0;
}
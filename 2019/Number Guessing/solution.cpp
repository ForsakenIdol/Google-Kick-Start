#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    int T; // Number of test cases
    cin >> T;
    for (int i = 0; i < T; i++) {
        int A; int B; // Upper and lower bounds
        cin >> A >> B;
        int N; // Maximum number of guesses
        cin >> N;
        int guessNum = 0;
        bool done = false; // Exit early if guess is correct
        
        // Binary search routine
        while (guessNum <= N && !done) {
            guessNum++;
            int mid = (A + B) / 2;
            if (mid <= A) mid = A + 1; if (mid > B) mid = B;
            cout << mid << "\n";
            // Parse response from judge
            string response;
            cin >> response;
            if (response == "CORRECT") done = true;
            else if (response == "TOO_SMALL") A = mid + 1;
            else if (response == "TOO_BIG") B = mid - 1;
            else {
                fprintf(stderr, "Error in response handling on iteration %d.\n" , guessNum);
                return 1;
            }
        }
    }
    return 0;
}
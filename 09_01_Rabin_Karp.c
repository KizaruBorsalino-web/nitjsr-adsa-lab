#include <stdio.h>
#include <string.h>
#include <math.h>

#define d 256       // Number of characters in input alphabet (ASCII)
#define q 101       // A prime number for hashing (to minimize collisions)

// Rabin-Karp String Matching Function
void rabinKarpSearch(char pattern[], char text[]) {
    int M = strlen(pattern);
    int N = strlen(text);
    int i, j;
    int p = 0;  // Hash value for pattern
    int t = 0;  // Hash value for text window
    int h = 1;
    int found = 0;

    // The value of h would be "pow(d, M-1) % q"
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of pattern and first window of text
    for (i = 0; i < M; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++) {
        // If hash values match, check characters one by one
        if (p == t) {
            for (j = 0; j < M; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }

            if (j == M) {
                printf("Pattern found at index %d\n", i);
                found = 1;
            }
        }

        // Calculate hash for next window of text
        if (i < N - M) {
            t = (d * (t - text[i] * h) + text[i + M]) % q;

            // We might get negative value of t, converting it to positive
            if (t < 0)
                t = (t + q);
        }
    }

    if (!found)
        printf("Pattern not found in the text.\n");
}

// Main function to take generalized input
int main() {
    char text[1000], pattern[1000];

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';

    rabinKarpSearch(pattern, text);

    return 0;
}

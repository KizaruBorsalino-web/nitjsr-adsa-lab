#include <stdio.h>
#include <string.h>

// Function to compute the Longest Prefix Suffix (LPS) array
void computeLPSArray(char* pattern, int M, int* lps) {
    int len = 0;  // length of the previous longest prefix suffix
    int i = 1;
    lps[0] = 0;   // lps[0] is always 0

    while (i < M) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0)
                len = lps[len - 1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP Search Function
void KMPSearch(char* pattern, char* text) {
    int M = strlen(pattern);
    int N = strlen(text);

    int lps[M];
    int i = 0;  // index for text[]
    int j = 0;  // index for pattern[]
    int found = 0;

    // Preprocess the pattern (calculate LPS array)
    computeLPSArray(pattern, M, lps);

    while (i < N) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == M) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
            found = 1;
        }
        // mismatch after j matches
        else if (i < N && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    if (!found)
        printf("Pattern not found in the text.\n");
}

// Main function for generalized input
int main() {
    char text[1000], pattern[1000];

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';

    KMPSearch(pattern, text);

    return 0;
}

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define NO_OF_CHARS 256  // Total ASCII characters

// Function to preprocess the pattern and create the bad character heuristic table
void badCharHeuristic(char *pattern, int size, int badchar[NO_OF_CHARS]) {
    int i;

    // Initialize all occurrences as -1
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    // Fill the actual value of the last occurrence of a character in the pattern
    for (i = 0; i < size; i++)
        badchar[(unsigned char)pattern[i]] = i;
}

// Boyer-Moore Search Function using Bad Character Heuristic
void BoyerMooreSearch(char *text, char *pattern) {
    int m = strlen(pattern);
    int n = strlen(text);

    int badchar[NO_OF_CHARS];
    int found = 0;

    // Preprocess the pattern
    badCharHeuristic(pattern, m, badchar);

    int s = 0;  // shift of the pattern with respect to text
    while (s <= (n - m)) {
        int j = m - 1;

        // Keep reducing index j while characters of pattern and text are matching
        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        // If the pattern is present at current shift
        if (j < 0) {
            printf("Pattern found at index %d\n", s);
            found = 1;

            // Shift the pattern so that next possible match can be checked
            s += (s + m < n) ? m - badchar[(unsigned char)text[s + m]] : 1;
        } else {
            // Shift the pattern so that bad character in text aligns with the last occurrence in pattern
            int shift = j - badchar[(unsigned char)text[s + j]];
            s += (shift > 1) ? shift : 1;
        }
    }

    if (!found)
        printf("Pattern not found in the text.\n");
}

// Main function for user input
int main() {
    char text[1000], pattern[1000];

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove newline

    printf("Enter the pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';

    BoyerMooreSearch(text, pattern);

    return 0;
}

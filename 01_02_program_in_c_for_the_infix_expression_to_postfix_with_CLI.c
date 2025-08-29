#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const char *expr;
int pos = 0;

int parse_expression();

int parse_number() {
    int num = 0;
    while (isdigit(expr[pos])) {
        num = num * 10 + (expr[pos] - '0');
        pos++;
    }
    return num;
}

int parse_factor() {
    int val = 0;
    if (expr[pos] == '(') {
        pos++;  // skip '('
        val = parse_expression();
        if (expr[pos] == ')') pos++;  // skip ')'
    } else {
        val = parse_number();
    }
    return val;
}

int parse_term() {
    int val = parse_factor();
    while (expr[pos] == '*' || expr[pos] == '/') {
        char op = expr[pos++];
        int next_factor = parse_factor();
        if (op == '*')
            val *= next_factor;
        else {
            if (next_factor == 0) {
                printf("Error: Division by zero\n");
                exit(EXIT_FAILURE);
            }
            val /= next_factor;
        }
    }
    return val;
}

int parse_expression() {
    int val = parse_term();
    while (expr[pos] == '+' || expr[pos] == '-') {
        char op = expr[pos++];
        int next_term = parse_term();
        if (op == '+')
            val += next_term;
        else
            val -= next_term;
    }
    return val;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s \"<expression>\"\n", argv[0]);
        return 1;
    }
    expr = argv[1];
    pos = 0;

    // Skip spaces before parsing
    while (expr[pos] == ' ') pos++;

    printf("%d\n", parse_expression());
    return 0;
}


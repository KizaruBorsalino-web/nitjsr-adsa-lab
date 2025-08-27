#include <stdio.h>
#include <ctype.h>

#define MAX_SIZE 100

// Simple stack structure for chars (operators)
typedef struct {
    char data[MAX_SIZE];
    int top;
} CharStack;

// Initialize the stack
void stackInit(CharStack *stack) {
    stack->top = -1;
}

// Check if stack is empty
int stackEmpty(CharStack *stack) {
    return stack->top == -1;
}

// Push char onto stack
void stackPush(CharStack *stack, char c) {
    if (stack->top < MAX_SIZE - 1)
        stack->data[++stack->top] = c;
}

// Pop char from stack
char stackPop(CharStack *stack) {
    if (!stackEmpty(stack))
        return stack->data[stack->top--];
    return '\0';  // Return null char if empty
}

// Peek top char without popping
char stackPeek(CharStack *stack) {
    if (!stackEmpty(stack))
        return stack->data[stack->top];
    return '\0';
}

// Return precedence level (higher number = higher precedence)
int getPrecedence(char op) {
    switch (op) {
        case '/': return 3;
        case '*': return 2;
        case '+': return 1;
        case '-': return 0;
        default: return -1;
    }
}

// Convert infix expression to postfix expression
void convertInfixToPostfix(const char *infix, char *postfix) {
    CharStack operators;
    stackInit(&operators);

    int j = 0;  // Index for postfix output

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isdigit(ch)) {
            // Directly append digits (operands)
            postfix[j++] = ch;
        } else if (ch == '(') {
            stackPush(&operators, ch);
        } else if (ch == ')') {
            // Pop until '('
            while (!stackEmpty(&operators) && stackPeek(&operators) != '(') {
                postfix[j++] = stackPop(&operators);
            }
            if (!stackEmpty(&operators))
                stackPop(&operators);  // Remove '(' from stack
        } else {  // Operator
            while (!stackEmpty(&operators) && stackPeek(&operators) != '(' &&
                   getPrecedence(stackPeek(&operators)) >= getPrecedence(ch)) {
                postfix[j++] = stackPop(&operators);
            }
            stackPush(&operators, ch);
        }
    }

    // Pop any remaining operators
    while (!stackEmpty(&operators)) {
        postfix[j++] = stackPop(&operators);
    }

    postfix[j] = '\0';  // Null-terminate postfix string
}

int main() {
    char infixExp[MAX_SIZE], postfixExp[MAX_SIZE];

    printf("Type your infix expression: ");
    fgets(infixExp, MAX_SIZE, stdin);

    // Remove trailing newline from fgets input
    int len = 0;
    while (infixExp[len] != '\0') {
        if (infixExp[len] == '\n') {
            infixExp[len] = '\0';
            break;
        }
        len++;
    }

    convertInfixToPostfix(infixExp, postfixExp);

    printf("Converted postfix: %s\n", postfixExp);

    return 0;
}

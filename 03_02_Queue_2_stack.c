// Implement a queue using two stacks by Method-1 (costly Push/enqueue)
// and Method-2 (costly Pop/dequeue). Simple, GCC-friendly C.

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

/* ------------------------------ Stack ------------------------------ */
typedef struct {
    int a[MAX];
    int top; // -1 => empty
} Stack;

void stack_init(Stack *s) { s->top = -1; }
int stack_is_empty(const Stack *s) { return s->top < 0; }
int stack_is_full(const Stack *s) { return s->top >= MAX - 1; }

void stack_push(Stack *s, int x) {
    if (stack_is_full(s)) {
        fprintf(stderr, "Stack overflow\n");
        exit(1);
    }
    s->a[++(s->top)] = x;
}

int stack_pop(Stack *s) {
    if (stack_is_empty(s)) {
        fprintf(stderr, "Stack underflow\n");
        exit(1);
    }
    return s->a[(s->top)--];
}

int stack_peek(const Stack *s) {
    if (stack_is_empty(s)) {
        fprintf(stderr, "Stack empty\n");
        exit(1);
    }
    return s->a[s->top];
}

/* ----------------- Method 1: Costly enqueue (push) ----------------- */
/* Maintain queue order in s1 with front at top of s1. */
typedef struct {
    Stack s1, s2;
    int size;
} QueueCostlyEnq;

void q1_init(QueueCostlyEnq *q) {
    stack_init(&q->s1);
    stack_init(&q->s2);
    q->size = 0;
}

int q1_is_empty(const QueueCostlyEnq *q) { return q->size == 0; }

void q1_enqueue(QueueCostlyEnq *q, int x) {
    if (q->size >= MAX) {
        fprintf(stderr, "Queue overflow (q1)\n");
        exit(1);
    }
    // Move all from s1 -> s2
    while (!stack_is_empty(&q->s1)) stack_push(&q->s2, stack_pop(&q->s1));
    // Push new into s1
    stack_push(&q->s1, x);
    // Move back s2 -> s1
    while (!stack_is_empty(&q->s2)) stack_push(&q->s1, stack_pop(&q->s2));
    q->size++;
}

int q1_dequeue(QueueCostlyEnq *q) {
    if (q1_is_empty(q)) {
        fprintf(stderr, "Queue underflow (q1)\n");
        exit(1);
    }
    q->size--;
    return stack_pop(&q->s1);
}

/* ----------------- Method 2: Costly dequeue (pop) ------------------ */
/* Enqueue to s1; for dequeue, move s1 -> s2 only when needed. */
typedef struct {
    Stack s1, s2;
    int size;
} QueueCostlyDeq;

void q2_init(QueueCostlyDeq *q) {
    stack_init(&q->s1);
    stack_init(&q->s2);
    q->size = 0;
}

int q2_is_empty(const QueueCostlyDeq *q) { return q->size == 0; }

void q2_enqueue(QueueCostlyDeq *q, int x) {
    if (q->size >= MAX) {
        fprintf(stderr, "Queue overflow (q2)\n");
        exit(1);
    }
    stack_push(&q->s1, x);
    q->size++;
}

static void q2_move_if_needed(QueueCostlyDeq *q) {
    if (!stack_is_empty(&q->s2)) return;
    while (!stack_is_empty(&q->s1)) stack_push(&q->s2, stack_pop(&q->s1));
}

int q2_dequeue(QueueCostlyDeq *q) {
    if (q2_is_empty(q)) {
        fprintf(stderr, "Queue underflow (q2)\n");
        exit(1);
    }
    q2_move_if_needed(q);
    q->size--;
    return stack_pop(&q->s2);
}

int main(void) {
    printf("Method 1 (costly enqueue):\n");
    QueueCostlyEnq q1; q1_init(&q1);
    q1_enqueue(&q1, 10);
    q1_enqueue(&q1, 20);
    q1_enqueue(&q1, 30);
    printf("%d\n", q1_dequeue(&q1)); // 10
    q1_enqueue(&q1, 40);
    while (!q1_is_empty(&q1)) printf("%d\n", q1_dequeue(&q1)); // 20 30 40

    printf("\nMethod 2 (costly dequeue):\n");
    QueueCostlyDeq q2; q2_init(&q2);
    q2_enqueue(&q2, 100);
    q2_enqueue(&q2, 200);
    q2_enqueue(&q2, 300);
    printf("%d\n", q2_dequeue(&q2)); // 100
    q2_enqueue(&q2, 400);
    while (!q2_is_empty(&q2)) printf("%d\n", q2_dequeue(&q2)); // 200 300 400

    return 0;
}
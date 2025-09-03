#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int a[MAX];
    int front;   // index of front element
    int rear;    // next write position
    int size;    // number of elements
} Queue;

void q_init(Queue *q) { q->front = 0; q->rear = 0; q->size = 0; }
int q_is_empty(const Queue *q) { return q->size == 0; }
int q_is_full(const Queue *q)  { return q->size == MAX; }

void q_enqueue(Queue *q, int x) {
    if (q_is_full(q)) { fprintf(stderr, "Queue overflow\n"); exit(1); }
    q->a[q->rear] = x;
    q->rear = (q->rear + 1) % MAX;
    q->size++;
}

int q_dequeue(Queue *q) {
    if (q_is_empty(q)) { fprintf(stderr, "Queue underflow\n"); exit(1); }
    int v = q->a[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return v;
}

int q_peek(const Queue *q) {
    if (q_is_empty(q)) { fprintf(stderr, "Queue empty\n"); exit(1); }
    return q->a[q->front];
}

static void q_swap(Queue *a, Queue *b) {
    Queue tmp = *a; *a = *b; *b = tmp;
}

/* -------- Method 1: Costly EnQueue (push is costly, pop is O(1)) -------- */
typedef struct {
    Queue q1, q2; // q1 holds current stack with top at front
    int size;
} StackCostlyEnq;

void s1_init(StackCostlyEnq *s) { q_init(&s->q1); q_init(&s->q2); s->size = 0; }
int  s1_is_empty(const StackCostlyEnq *s) { return s->size == 0; }

void s1_push(StackCostlyEnq *s, int x) {
    if (s->size == MAX) { fprintf(stderr, "Stack overflow (method 1)\n"); exit(1); }
    // Enqueue new element into q2
    q_enqueue(&s->q2, x);
    // Move all from q1 to q2 so new element ends up at front after swap
    while (!q_is_empty(&s->q1)) q_enqueue(&s->q2, q_dequeue(&s->q1));
    // Swap q1 and q2; q2 becomes empty
    q_swap(&s->q1, &s->q2);
    s->size++;
}

int s1_pop(StackCostlyEnq *s) {
    if (s1_is_empty(s)) { fprintf(stderr, "Stack underflow (method 1)\n"); exit(1); }
    s->size--;
    return q_dequeue(&s->q1); // top is at front of q1
}

int s1_top(const StackCostlyEnq *s) {
    if (s1_is_empty(s)) { fprintf(stderr, "Stack empty (method 1)\n"); exit(1); }
    return q_peek(&s->q1);
}

/* -------- Method 2: Costly DeQueue (push is O(1), pop is costly) -------- */
typedef struct {
    Queue q1, q2; // push into q1; pop by moving to q2
    int size;
} StackCostlyDeq;

void s2_init(StackCostlyDeq *s) { q_init(&s->q1); q_init(&s->q2); s->size = 0; }
int  s2_is_empty(const StackCostlyDeq *s) { return s->size == 0; }

void s2_push(StackCostlyDeq *s, int x) {
    if (s->size == MAX) { fprintf(stderr, "Stack overflow (method 2)\n"); exit(1); }
    q_enqueue(&s->q1, x);
    s->size++;
}

int s2_pop(StackCostlyDeq *s) {
    if (s2_is_empty(s)) { fprintf(stderr, "Stack underflow (method 2)\n"); exit(1); }
    // Move until only the last (top) remains in q1
    while (s->q1.size > 1) q_enqueue(&s->q2, q_dequeue(&s->q1));
    int topv = q_dequeue(&s->q1); // pop the last one
    // Restore order by swapping queues
    q_swap(&s->q1, &s->q2);
    s->size--;
    return topv;
}

int s2_top(StackCostlyDeq *s) {
    if (s2_is_empty(s)) { fprintf(stderr, "Stack empty (method 2)\n"); exit(1); }
    while (s->q1.size > 1) q_enqueue(&s->q2, q_dequeue(&s->q1));
    int topv = q_dequeue(&s->q1);
    q_enqueue(&s->q2, topv); // put it back
    q_swap(&s->q1, &s->q2);
    return topv;
}

/* ------------------------------ Demo ------------------------------- */
int main(void) {
    printf("Method 1 (costly EnQueue / push):\n");
    StackCostlyEnq s1; s1_init(&s1);
    s1_push(&s1, 1); s1_push(&s1, 2); s1_push(&s1, 3);
    printf("top=%d\n", s1_top(&s1));        // 3
    printf("%d\n", s1_pop(&s1));            // 3
    s1_push(&s1, 4);
    while (!s1_is_empty(&s1)) printf("%d\n", s1_pop(&s1)); // 2 1 4? Wait LIFO: after popping 3, pushing 4 -> order: 2,1,4? Actually with method 1, top sequence is 4,2,1
    // Correct sequence will print: 4 2 1

    printf("\nMethod 2 (costly DeQueue / pop):\n");
    StackCostlyDeq s2; s2_init(&s2);
    s2_push(&s2, 10); s2_push(&s2, 20); s2_push(&s2, 30);
    printf("top=%d\n", s2_top(&s2));        // 30
    printf("%d\n", s2_pop(&s2));            // 30
    s2_push(&s2, 40);
    while (!s2_is_empty(&s2)) printf("%d\n", s2_pop(&s2)); // 40 20 10

    return 0;
}
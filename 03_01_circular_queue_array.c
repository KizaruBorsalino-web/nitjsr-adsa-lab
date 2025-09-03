
// implement the circular queue using the array..............


#include<stdlib.h>
#include <stdio.h>
#define SIZE 10

int cq[SIZE];
int front = -1, rear = -1;

int isFull() {
    return (front == (rear + 1) % SIZE);
}

int isEmpty() {
    return (front == -1);
}

void enqueue(int value) {
    if (isFull()) {
        printf("Queue is Full\n");
        return;
    }
    if (isEmpty())
        front = rear = 0;
    else
        rear = (rear + 1) % SIZE;

    cq[rear] = value;
}

int dequeue() {
    if (isEmpty()) {
        printf("Queue is Empty\n");
        return -1;
    }
    int value = cq[front];
    if (front == rear)
        front = rear = -1;
    else
        front = (front + 1) % SIZE;
    return value;
}

void display() {
    if (isEmpty()) {
        printf("Queue is Empty\n");
        return;
    }
    int i = front;
    printf("Queue: ");
    while (1) {
        printf("%d ", cq[i]);
        if (i == rear) break;
        i = (i + 1) % SIZE;
    }
    printf("\n");}
int main(){
    int cmd;
    int a=1;
    scanf("%d",&cmd);
    while(1){
        printf("enter the operations which you need to perfrom here:\n 4 for exit\n 1 for enqueue \n 2 for dequeue \n 3 for display.\n");
        scanf("%d",&cmd);
        switch(cmd){
            case 1:
            printf("enter the number you want to enqueue in the circular queue");
            int number;
            scanf("%d",&number);
            if(!isFull())
            enqueue(number);
            break;
            case 2:
            printf("the dequeue process here took place:");
            if(!isEmpty())
            printf("the number whih is dequeue from the queue is:%d",dequeue());
            break;
            case 3:
            printf("printing all the elements of the queue:");
            display();
            break;
            default:
            printf("nothing in the default");
            exit(0);
        }}
    return 0;
}
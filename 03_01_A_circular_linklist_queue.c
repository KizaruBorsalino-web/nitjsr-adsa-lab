#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node *front = NULL, *rear = NULL;

void enqueue(int value) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = value;
    temp->next = NULL;

    if (!front)
        front = rear = temp;
    else {
        rear->next = temp;
        rear = temp;
    }
}

int dequeue() {
    if (!front) {
        printf("Queue is Empty\n");
        return -1;
    }
    Node* temp = front;
    int value = temp->data;
    front = front->next;
    if (!front)
        rear = NULL;
    free(temp);
    return value;
}
void display() {
    Node* temp = front;
    if (!temp) {
        printf("Queue is Empty\n");
        return;
    }
    printf("Queue: ");
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
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
            enqueue(number);
            break;
            case 2:
            printf("the dequeue process here took place:");
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

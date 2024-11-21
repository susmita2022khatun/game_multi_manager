#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *front;
    Node *rear;
    int size;
} Queue;

// Function prototypes
void init_queue(Queue *q);
int is_empty(Queue *q);
void enqueue(Queue *q, int data);
int dequeue(Queue *q);

#endif // QUEUE_H


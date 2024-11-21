#include "queue.h"

// Initialize the queue
void init_queue(Queue *q) {
    q->front = q->rear = NULL;
    q->size = 0;
}

// Check if the queue is empty
int is_empty(Queue *q) {
    return q->size == 0;
}

// Add an element to the queue
void enqueue(Queue *q, int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
    q->size++;
}

// Remove an element from the queue
int dequeue(Queue *q) {
    if (is_empty(q)) {
        return -1; // Queue is empty
    }

    Node *temp = q->front;
    int data = temp->data;

    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    q->size--;

    return data;
}


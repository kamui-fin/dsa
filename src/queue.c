#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>

struct Node {
    int data;
    struct Node* next;
};

struct ListQueue {
    struct Node* head;    
    struct Node* tail;    
};

void enqueue_lq(struct ListQueue* lq, int value) {
    struct Node *new_node = malloc(sizeof (struct Node));
    new_node->data = value;

    if (!lq->head) {
        lq->head = new_node;
        lq->tail = new_node;
    }
    else {
        lq->tail->next = new_node;
        lq->tail = new_node;
    }
}

struct Node* dequeue_lq(struct ListQueue* lq) {
    struct Node* head = lq->head;
    struct Node* temp = head->next;
    head->next = NULL;
    lq->head = temp;
    return head;
}

bool empty_lq(struct ListQueue* lq) {
    return lq->head == NULL;
}

void print_lq(struct ListQueue* lq) {
    while (lq->head != NULL) {
        printf("%d ", lq->head->data);
        lq->head = lq->head->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    struct ListQueue lq = {
        .head = head,
        .tail = tail
    };
}
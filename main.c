#include <stdio.h>
#include <stdlib.h>
typedef struct node Node;
struct node {
    int data;
    Node* next;
};
struct Queue {
    Node* head;
    Node* tail;
};
typedef struct Queue Queue;
enum status {
    FAILURE, SUCCESS
};
typedef enum status Status;

Queue* createQueue(int val);

Status insert(Queue*, int);

Status service(Queue*);

int front(Queue*);

int is_empty(Queue*);

Status destroy_queue(Queue*);

int main(int argc, char * argv[]) {
    /*
     *first line the the # of inputs
     *line after is the dimensions and l and m
     *l = length of ferry in meters
     *m = amount of cars
     *lines following lenght of cars in cm and whether they are on the right or left
     */
    Queue * q = createQueue(1);
    insert(q, 2);
    insert(q, 3);
    printf("%d\n", front(q));
    service(q);
    printf("%d\n", front(q));
    service(q);
    printf("%d\n", front(q));
    service(q);
    printf("%d\n", is_empty(q));



    destroy_queue(q); // this only destroys the queue struct make sure that all nodes are freed before this call
    return 0;
}
Queue* createQueue(int val) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q!=NULL) {
        q->head = NULL;
        insert(q, val);
            //the length is one when created
            q -> tail = q-> head;
        }
    return q;
    }

Status insert(Queue* q, int data) {
    if (q==NULL) {
        return FAILURE;
    }
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node!= NULL) {
        new_node -> data = data;
        new_node -> next = NULL;
        if (q->head == NULL) {
            q->head = new_node;
            q -> tail = new_node;
            printf("inserted node %d at %p\n", new_node->data, new_node);
            return SUCCESS;
        } else {
            while (q -> tail -> next != NULL) {
                q -> tail = q -> tail -> next;
            }
            q -> tail -> next = new_node;
            q -> tail = new_node;
            printf("inserted node %d at %p\n", new_node->data, new_node);
            return SUCCESS;
        }
    }
    return FAILURE;
}

Status service(Queue* q) {
    if (q->head!=NULL) {
        Node* delete_me =  q->head;
        q->head = q -> head -> next;
        printf("servicing %d\n", delete_me->data);
        free(delete_me);
        return SUCCESS;
    }
    return FAILURE;
}

int front(Queue* q) {
    if (q!=NULL && q -> head != NULL) {
        return q->head -> data;
    }
    else printf("Queue is empty\n");
    return -1;
}

int is_empty(Queue* q) {
   return(q == NULL || q->head ==NULL) ? 1 : 0;
}

Status destroy_queue(Queue* q) {
    if (q != NULL) {
        free(q);
        //dont need to null out the head and the tail as they are freed & nulled by service, additional frees lead to undefined behavior
        return SUCCESS;
    }
    printf("unaccessible queue\n");
    return FAILURE;
}
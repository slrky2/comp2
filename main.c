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
    int capacity;
    int size;
};
typedef struct Queue Queue;
enum status {
    FAILURE, SUCCESS
};
typedef enum status Status;

Queue* createQueue(int cap);

Status insert(Queue*, int);

Status service(Queue*);

int front(Queue*);

int is_empty(Queue*);

Status destroy_queue(Queue*);

void clear_key_buffer(void);

int ferry(int, int, char, Queue*, Queue*, int*, int*);

int main(int argc, char * argv[]) {
    /*
     *first line the the # of inputs
     *line after is the dimensions and l and m
     *l = length of ferry in meters
     *m = amount of cars
     *lines following lenght of cars in cm and whether they are on the right or left
     */
    //todo make sure to update size and capacity in every function new variables in the queue struct
    //todo it may be easier to keep the sizes as local in main in that case we dont need size and capacity in the struct
    int num;
    int cars;
    int ferry_length;
    int size=0;
    int car_length;
    char direction;
    int switches = 1;
    Queue* left = NULL;
    Queue* right = NULL;

    scanf("%d", &num);
    //just getting info to begin the evaulation
    for (int i = 0; i < num; i++) {
        printf("%d\n", num);
        clear_key_buffer();
        scanf("%d", &ferry_length);
        scanf("%d", &cars);
        clear_key_buffer();
        printf("%d\n", ferry_length);
        printf("%d\n", cars);



        //initialize the queues
        left = createQueue(cars);
        right = createQueue(cars);
    }
    char directions[cars];
        //this is setting up the queues
        // todo make sure that the case given in the pdf actaully works currently doesnt run
        for (int j = 0; j < cars; j++) {
            scanf("%d", &car_length);
            printf("lenght of the car %d\n", car_length);
            scanf(" %c", &direction);
            printf("direction = %c\n", direction);
            directions[j] = direction;
            clear_key_buffer(); // we only need to know the first letter of the direction
            //todo create the queues
            switch (direction) {
                case 'r':
                    insert(right, car_length);
                break;
                case 'l':
                    insert(left, car_length);
                break;
                default: printf("couldnt evaulate direction\n");
            }



// todo do the work pop off the respective queue if the car can fit  on the ferry

        }
    for (int i = 1; i < cars; i++) {
        if (directions[i] != directions[i-1]) {
            switches++;
        }
        switch (directions[i]) { // theres an issure here
            case 'r':
                if (ferry_length >= front(right)/100) {
                    size += front(right)/100;
                    service(right);
                } else {
                    switches++;
                    size = front(left)/100;
                    service(left);
                }
            break;
            case 'l':
                if (ferry_length >= front(left)/100) {
                    size += front(left)/100;
                    service(left);
                } else {
                    switches++;
                    size = front(right)/100;
                    service(right);
                }
            default:
        }
    }
    printf("there will be atleast %d switches\n", switches); //evaluates the least amount of possible switches necessary

    while (!is_empty(left)) {
        printf("left %d \t", front(left));
        service(left);
    }
    while (!is_empty(right)) {
        printf("right %d \t", front(right));
        service(right);
    }


    destroy_queue(left); // this only destroys the queue struct make sure that all nodes are freed before this call
    destroy_queue(right);
    return 0;
}

// cm = m/100
// the function should start with the direction that was stated first
// int ferry(int ferry_length, int car_length, char direction, Queue* left, Queue* right, int* switches, int* size) {
//         switch (direction) {
//             case 'r':
//                 if (ferry_length >= front(right)/100) {
//                     *size += front(right)/100;
//                     service(right);
//                 } else {
//                     *switches++;
//                     *size += front(left)/100;
//                     service(left);
//                 }
//             break;
//             case 'l':
//                 if (ferry_length >= front(left)/100) {
//                     *size += front(left)/100;
//                     service(left);
//                 } else {
//                     *switches++;
//                     *size += front(right)/100;
//                     service(right);
//                 }
//             default:
//         }
//     return *switches;
// }



Queue* createQueue(int cap) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q!=NULL) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
        q -> capacity = cap;
        return q;
    }
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

            } else {
                while (q -> tail -> next != NULL) {
                    q -> tail = q -> tail -> next;
                }
                q -> tail -> next = new_node;
                q -> tail = new_node;
                printf("inserted node %d at %p\n", new_node->data, new_node);

            }
        }
        q->size++;
        return SUCCESS;
    }


Status service(Queue* q) {
    if (q->head!=NULL) {
        Node* delete_me =  q->head;
        q->head = q -> head -> next;
        printf("servicing %d\n", delete_me->data);
        free(delete_me);
        q->size--;
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

void clear_key_buffer(void) {
    char c;
    scanf("%c", &c);
    while (c != '\n') {
        scanf("%c", &c);
    }
}
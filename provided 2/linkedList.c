#include <stdio.h>
#include <stdlib.h>

//Linked List nodes struct
struct node{
    int value;
    struct node *next;
};
typedef struct node node_t;

void printList(node_t *head);

node_t *createNewNode(int value);

void insertNode(node_t **head, node_t* newNode);

void deleteNode(node_t **head, int value);

void freeList(node_t* head);

int main(int argc, char* argv[]){
    //creates head node for linked list
    node_t *head = NULL;

    if (argc == 1){
        printf("error\n");
        return 0;
    }

    //reads file from command line
    FILE* fp = fopen(argv[1], "r");

    while (1){
        int data;
        char kate;
        int n = fscanf(fp, "%c\t%d\n", &kate, &data);
        if (n != 2){
            break;
        } else if (kate == 'i'){
            insertNode(&head, createNewNode(data));
        } else if (kate == 'd'){
            deleteNode(&head, data);
        }
    }
    fclose(fp);

    int length;
    node_t* counter = head;
    while (counter != NULL){
        length++;
        counter = counter->next;
    }
    printf("%d\n", length);

    printList(head);
    freeList(head);
    return 0;
}

void printList(node_t *head){
    node_t* current = head->next;
    node_t* prev = head;
    if (prev == NULL) return;
    while (current != NULL){
        if(prev->value != current->value){
            printf("%d\t", prev->value);
            prev = current;
        }
        if(current->next == NULL ){
            printf("%d\t", current->value);
        }
        current = current->next;
    }
    printf("\n");
}

node_t *createNewNode(int value){
    node_t *result = malloc(sizeof(node_t));
    result->value = value;
    result->next = NULL;
    return result;
}

void insertNode(node_t **head, node_t* newNode){
    node_t* temp;
    if (*head == NULL || (*head)->value >= newNode->value){
        newNode->next = *head;
        *head = newNode;
    } else{
        temp = *head;
        while (temp->next != NULL && temp->next->value < newNode->value){
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void deleteNode(node_t **head, int data){
    node_t *temp = *head;
    node_t *prev;
    if (temp != NULL && temp->value == data){
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->value != data){
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;

    prev->next = temp->next;

    free(temp);
    free(prev);
}

void freeList(node_t* head){
    node_t* temp;
    while(head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
}
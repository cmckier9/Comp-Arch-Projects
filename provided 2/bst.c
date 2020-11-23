#include <stdio.h>
#include <stdlib.h>

struct node{
    int value;
    struct node* left;
    struct node* right;
};
typedef struct node node_t;

node_t *createNewNode(int value);

node_t* insertNode(node_t* head, int value);

void freeBST(node_t* head);

void inOrder(node_t* head){
    if (head != NULL){
        inOrder(head->left);
        printf("%d\t", head->value);
        inOrder(head->right);
    }
}

int main(int argc, char* argv[]){
    //Initializes head of BST
    node_t *head = NULL;

    if (argc == 1){
        printf("error\n");
        return 0;
    }

    FILE* fp = fopen(argv[1], "r");
    while(1){
        char kate;
        int newNum;
        int n = fscanf(fp, "%c\t%d\n", &kate, &newNum);
        if (n != 2) break;
        if (kate == 'i'){
            head = insertNode(head, newNum);
        }
    }
    fclose(fp);

    inOrder(head);
    printf("\n");
    freeBST(head);
    return 0;

}

node_t *createNewNode(int value){
    node_t *result = (node_t*) malloc(sizeof(node_t));
    result->value = value;
    result->left = NULL;
    result->right = NULL;
    return result;
}

node_t* insertNode(node_t* head, int value){
    if (head == NULL){
        return createNewNode(value);
    }
    if (value < head->value){
        head->left = insertNode(head->left, value);
    } else if (value > head->value){
        head->right = insertNode(head->right, value);
    }

    return head;
}

void freeBST(node_t* head){
    if (head != NULL){
        freeBST(head->right);
        freeBST(head->left);
        free(head);
    }
}
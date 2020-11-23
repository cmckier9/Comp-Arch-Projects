#include <stdio.h>
#include <stdlib.h>

int collisions = 0;
int searches = 0;

struct node{
    int key;
    int value;
    struct node *next;
};
typedef struct node node_t;

//Hash table item defined here
struct hashItem{
    node_t* head;
};
typedef struct hashItem hashItem;

//Initializes hash table with size 10000
hashItem* array;

//Headers for functions
int hashFunction (int key);
void createArray();
void insert(int key, int value);
int findIndex(node_t* list, int key);
int search(int key, int value);
void freeList(node_t* head);
// void display();


int main(int argc, char* argv[]){
    //Creates and initializes hash table
    array = (hashItem*) malloc(10000 * sizeof(hashItem*));
    createArray();

    //Reads file
    FILE* fp = fopen(argv[1], "r");
    while (1){
        char kate;
        int data;
        int n = fscanf(fp, "%c\t%d\n", &kate, &data);
        if (n != 2){
            break;
        }//Inserts value in to hash table 
        else if (kate == 'i'){
            insert(hashFunction(data), data);
        }//Searches hash table for value 
        else if (kate == 's'){
            int temp;
            temp = search(hashFunction(data), data);
            if (temp != 0){
                searches++;
            }
        }
    }
    fclose(fp);
    //Prints succesfull searches and collisions
    printf("%d\n", collisions);
    printf("%d\n", searches);
    // display();
    for (int i = 0; i < 10000; i++){
        freeList(array[i].head);
    }
    free(array);
    return 0;
}

int hashFunction(int num){
    int key;
    if(num<0){
        key=(num*-1) % 10000;
    }else{
        key=num%10000;
    }
    return key;
}

void createArray(){
    for (int i = 0; i < 10000; i++){
        array[i].head = NULL;
    }
}

void insert(int index, int num){

    //Gets linked list at the index
    node_t* list = (node_t*) array[index].head;

    //Creates node to insert in to list at current index
    node_t* item = (node_t*) malloc(sizeof(node_t));
    item->key = index;
    item->value = num;
    item->next = NULL;

    //inserts at head of linked list if list is empty
    if(list == NULL){
        array[index].head = item;
    } else{
        collisions++;
        node_t* ptr = array[index].head;
        node_t* ptr2 = NULL;
        while (ptr != NULL){
            if (ptr->value == num){
                return;
            }
            ptr2 = ptr;
            ptr = ptr->next;
        }
        ptr2->next = item;
    }
}

int findIndex(node_t* list, int key){
    int retval = 0;
	struct node *temp = list;
	while (temp != NULL) 
        {
		if (temp->key == key){
			return retval;
		}
  		temp = temp->next;
		retval++;
	}
	return -1;
}

int search(key, num){
    if(array[key].head == NULL){
        return 0;//absent
    }
    if(array[key].head->value == num){
        return 1;//present
    }
    node_t* point=array[key].head;

    while(point!=NULL){
        if(point->value==num){
        return 1;//present
        }
    point=point->next;
    }

    return 0;//absent
}

void freeList(node_t* head){
    node_t* temp;
    while(head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
}

// void display()
// {
// 	int i = 0;
// 	for (i = 0; i < 10000; i++) 
//         {
// 		struct node *temp = array[i].head;
// 		if (temp == NULL) 
//                 {
// 			printf("array[%d] has no elements\n", i);
 
// 		}
//                 else 
//                 {
// 			printf("array[%d] has elements-: ", i);
// 			while (temp != NULL)
//                         {
// 				printf("key= %d  value= %d\t", temp->key, temp->value);
// 				temp = temp->next;
// 			}
// 			printf("\n");
 
// 		}
// 	}
// }

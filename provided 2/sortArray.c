#include <stdio.h>

int main(int argc, char* argv[]){

    //reads file from command line
    FILE* fp = fopen(argv[1], "r");
    
    //Reads length of array and initializes an array of that length, print line is a test
    int length, temp;
    fscanf(fp, "%d", &length);
    // printf("%d\n", length);

    //Reads next line of document and inputs numbers into arr, 2nd loop prints numbers as a test
    int arr[length];
    for (int i = 0; i < length; i++){
        fscanf(fp, "%d\t", &arr[i]);
    }
    fclose(fp);
    // for (int i = 0; i < length; i++){
    //     printf("%d\t", arr[i]);
    // }
    // printf("\n");

    //Sorts the array by putting the evens before the odd
    for (int i = 0; i < length; i++){
        for (int j = i + 1; j < length; j++){
            if(arr[i] % 2 != 0 && arr[j] % 2 == 0){
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    //Sorts the even numbers to be in ascending order
    for (int i = 0; i < length; i++){
        for (int j = i + 1; j < length; j++){
            if ((arr[i] % 2 == 0 && arr[j] % 2 == 0) && (arr[i] > arr[j])){
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            } 
        }
    }

    //Sorts the odd numbers in descending order
    for (int i = 0; i < length; i++){
        for (int j = i + 1; j < length; j++){
            if ((arr[i] % 2 != 0 && arr[j] % 2 != 0) && (arr[i] < arr[j])){
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            } 
        }
    }

    //Prints array
    for (int i = 0; i < length; i++){
        printf("%d\t", arr[i]);
    }
    printf("\n");

    return 0;
}

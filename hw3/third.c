#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

unsigned short get(unsigned short num, int pos);

int main(int argc, char* argv[]){
    //Reads number from command
    unsigned short num = atoi(argv[1]);

    //Checks if number is a palindrome
    for (int i = 0; i < 8; i++){
        if (get(num, i) != get(num, 15-i)){
            printf("Not-Palindrome\n");
            return 0;
        }
    }
    printf("Is-Palindrome\n");
    return 0;
}


//Gets and display bit in given number at read position
unsigned short get(unsigned short num, int pos){
    num = num >> pos;
    if (num % 2 != 0){
        return 1;
    } else {
        return 0;
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void comp(unsigned short *num, unsigned short);
void set(unsigned short *num, unsigned short pos, unsigned short bit);
void get(unsigned short num, unsigned short pos);

int main(int argc, char* argv[]){
    
    //Variable for original value
    unsigned short x;
    //Reads file and sets up variable for original value
    FILE* fp = fopen(argv[1], "r");
    fscanf(fp, "%hu\n", &x);
    //printf("%hu\n", x);
    while(1){
        unsigned short pos;
        unsigned short bit;
        char s[5];
        int n = fscanf(fp, "%s\t%hu\t%hu\n", s, &pos, &bit);
        if(n != 3){
            break;
        } else if (strcmp(s, "comp") == 0){
            comp(&x, pos);
        } else if (strcmp(s, "get") == 0){
            get(x, pos);
        } else if (strcmp(s, "set") == 0){
            set(&x, pos, bit);
        }
    }
    fclose(fp);
    return 0;
}

//Finds compliment of read position and given number
void comp(unsigned short *num, unsigned short pos){
    unsigned short z = *num;
    z = z >> pos;
    unsigned short y;
    y = pow(2, pos);
    if (z % 2 == 0){
        *num = *num + y;
    } else {
        *num = *num - y;
    }
    printf("%hu\n", *num);
}

//Sets the read position of the given number to the read bit
void set(unsigned short *num, unsigned short pos, unsigned short bit){
    unsigned short z = *num;
    z = z >> pos;
    unsigned short y;
    y = pow(2, pos);
    if (z % 2 == 0){
        if (bit == 1){
            *num = *num + y;
        }
    } else {
        if (bit == 0){
            *num = *num - y;
        }
    }
    
    printf("%hu\n", *num);
}

//Gets and display bit in given number at read position
void get(unsigned short num, unsigned short pos){
    num = num >> pos;
    if (num % 2 != 0){
        printf("%d\n", 1);
    } else {
        printf("%d\n", 0);
    }
}
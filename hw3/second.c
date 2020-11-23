#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(int argc, char* argv[]){
    //Reads command line and creates array a size of an unsigned short in bits
    unsigned short num = atoi(argv[1]);

    //Counts pairs of ones in number
    unsigned short temp = num;
    unsigned short numPairs = 0;
    while(temp > 0){
        if (temp % 2 == 0){
            temp = temp >> 1;
            continue;
        }
        temp = temp >> 1;
        if (temp % 2 != 0){
            numPairs++;
            temp = temp >> 1;
        }
    }
    //printf("%hu\n", numPairs);
    
    //Counts number of ones in binary
    unsigned short temp2 = num;
    unsigned short numOnes = 0;
    for (int i = 0; i < 16; i++){
        if (temp2 % 2 == 1){
            numOnes++;
        }
        temp2 = temp2 >> 1;
    }
    //printf("%hu\n", numOnes);
    
    //Prints output
    if (numOnes % 2 == 0){
        printf("Even-Parity\t%hu\n", numPairs);
    } else {
        printf("Odd-Parity\t%hu\n", numPairs);
    }
    return 0;
}


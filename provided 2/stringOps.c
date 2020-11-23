#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
    if (argc == 1){
        printf("No string entered\n");
        return 1;
    }
    int vowelCounter = 0;
    for (int i = 1; i <argc; i++){
        int len = strlen(argv[i]);
        char* word = argv[i];
        for (int j = 0; j < len; j++){
            if (word[j] == 'A' || word[j] == 'E' || word[j] == 'I' || word[j] == 'O' || word[j] == 'U' ||
            word[j] == 'a' || word[j] == 'e' || word[j] == 'i' || word[j] == 'o' || word[j] == 'u'){
                vowelCounter++;
            }
        }
    }
    printf("%d\n", vowelCounter);
    char vowels[vowelCounter+1];
    vowels[vowelCounter] = '\0';
    int vowelsIndex = 0;
    for (int i = 1; i < argc; i++){
        int len = strlen(argv[i]);
        char* word = argv[i];
        for (int j = 0; j < len; j++){
            if (word[j] == 'A' || word[j] == 'E' || word[j] == 'I' || word[j] == 'O' || word[j] == 'U' ||
            word[j] == 'a' || word[j] == 'e' || word[j] == 'i' || word[j] == 'o' || word[j] == 'u'){
                vowels[vowelsIndex] = word[j];
                vowelsIndex++;
            }
        }
    }
    printf("%s\n", vowels);
}

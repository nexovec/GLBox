#include "utils.h"
#include "stdio.h"
#include "stdlib.h"

char* readStringFromFile(char* path){
    FILE* file = fopen(path,"r");
    char* contents = (char*)malloc(1000*sizeof(char));
    int i = 0;
    char character;
    while((character = fgetc(file)) != EOF){
        contents[i++] = character;
    }
    contents[i] = '\0';
    fclose(file);
    return contents;
}
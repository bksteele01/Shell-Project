#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 

int cat(char* file){
    FILE *catfile;
    catfile = fopen(file, "r");
    if(catfile == NULL){
        printf("file invalid\n");
        return 0;
    }
    char characters = fgetc(catfile);
    while(characters != EOF){
        printf("%c", characters);
        characters = fgetc(catfile);
    }
    fclose(catfile);
    return 1;
}
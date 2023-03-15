#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <fcntl.h>
#include<sys/wait.h>


int cat(char* file, char operator, char* redirfile){
    int pid = fork();
    if(pid < 0){
        printf("fork failed\n");
    }
    FILE *catfile;
    catfile = fopen(file, "r");
    if(catfile == NULL && pid > 0){
        printf("file invalid\n");
        return 0;
    }
    char characters = fgetc(catfile);
    if(operator == ' ' && pid > 0){
        while(characters != EOF){
            printf("%c", characters);
            characters = fgetc(catfile);
        }
    }
    if(operator == '>' && pid == 0){
        int pid, status;
        int infd, outfd;
        if ((infd = open(file, O_RDONLY, 0644)) < 0) {
            perror(file);
            exit(1);
        }
        if ((outfd = open(redirfile, O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) {
            perror(redirfile);
            exit(1);
        }
        dup2(infd,  0);
        dup2(outfd, 1);
        while(characters != EOF){
            printf("%c", characters);
            characters = fgetc(catfile);
        }
        char line[100];
        fgets(line, 100, stdin);
        fclose(catfile);
        exit(1);
    }
    if(pid == 0){
        exit(1);
    }
    if(pid > 0){
        wait(NULL);
    }
    fclose(catfile);
    return 1;
}
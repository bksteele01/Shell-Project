#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <fcntl.h>
#include<sys/wait.h>


int cat(char* file, char operator, char* redirfile){
    //fork
    int pid = fork();
    if(pid < 0){
        printf("fork failed\n");
    }

    //child makes operations
    if(pid == 0){

        //if input redirection, take file name from specified file
        //instead of through argument
        if(operator == '<'){
            int infd;
            if((infd = open(redirfile, O_RDONLY, 0644)) < 0) {
                perror(redirfile);
                exit(1);
            }
            dup2(infd,  0);
            fgets(file, 50, stdin);
            if(file[strlen(file)-1] == '\n'){
                file[strlen(file)-1] = '\0';
	        }	
        }

        //open file
        FILE *catfile;
        catfile = fopen(file, "r");
        
        if(catfile == NULL && pid > 0){
            printf("file invalid\n");
            exit(1);
        }
        char characters = fgetc(catfile);
        

        //if output redirect, hook stdout to file
        if(operator == '>'){
            int outfd;
            if ((outfd = open(redirfile, O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) {
                perror(redirfile);
                exit(1);
            }
            dup2(outfd, 1);
        }

        //print file contents
        while(characters != EOF){
            printf("%c", characters);
            characters = fgetc(catfile);
        }

        //close file and exit process
        fclose(catfile);
        exit(1);
        
    }

    //parent waits for child
    if(pid > 0 && operator != '&'){
        wait(NULL);
    }
    return 1;
}
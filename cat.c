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

    //child
    if(pid == 0){
        //open file
        
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
        FILE *catfile;
        catfile = fopen(file, "r");
        
        if(catfile == NULL && pid > 0){
            printf("file invalid\n");
            exit(1);
        }
        char characters = fgetc(catfile);
        

        //setting up redirection
        //if output redirect char, redirect
        if(operator == '>'){
            int outfd;
            if ((outfd = open(redirfile, O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) {
                perror(redirfile);
                exit(1);
            }
            dup2(outfd, 1);
        }

        //print
        while(characters != EOF){
            printf("%c", characters);
            characters = fgetc(catfile);
        }

        //close file and exit
        fclose(catfile);
        exit(1);
        
    }

    //wait for child
    if(pid > 0){
        wait(NULL);
    }
    return 1;
}
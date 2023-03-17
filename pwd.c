#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "cat.h"
#include "ls.h"
#include <dirent.h>
#include <signal.h>
#include<sys/wait.h>
#include <fcntl.h>

int pwd(char operator, char* file){
    //fork
    int pid = fork();

    //child does operations
    if(pid == 0){
        // get the current directory path
        char path[200];
        getcwd(path, 200);

        //if output redirect, redirect to specified file
        if(operator == '>'){
            int outfd;
            if ((outfd = open(file, O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) {
                perror(file);
                exit(1);
            }
            dup2(outfd, 1);
        }
        //print directory path, and then exit process
        printf("%s\n", path);
        exit(1);
    }
    //parent waits for child
    if(pid > 0){
        wait(NULL);
    }
    return 1;
}
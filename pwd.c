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
    int pid = fork();
    if(pid == 0){
        char path[200];
        // get the current directory path and print it 
        getcwd(path, 200);
        if(operator == '>'){
            int outfd;
            if ((outfd = open(file, O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) {
                perror(file);
                exit(1);
            }
            dup2(outfd, 1);
        }
        printf("%s\n", path);
        exit(1);
    }
    wait(NULL);
    return 1;
}
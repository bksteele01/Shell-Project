#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include<sys/wait.h>

int ls(char operator, char* file){
    int pid = fork();
    if(pid < 0){
        printf("fork failed\n");
    }

    if(pid == 0){
        struct dirent *direct;
        DIR *dr = opendir(".");
        if (dr == NULL && pid > 0){
            printf("Could not open current directory" );
            return 0;
        }
        if(operator == '>'){
            int outfd;
            if ((outfd = open(file, O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) {
                perror(file);
                exit(1);
            }
            dup2(outfd, 1);
        }
        while ((direct = readdir(dr)) != NULL)
            printf("%s\n", direct->d_name); 
        closedir(dr);
        exit(1);
    }
    if(pid > 1){
        wait(NULL);
    }
    return 0;
}

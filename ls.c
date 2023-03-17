#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include<sys/wait.h>

int ls(char operator, char* file, int thef[]){
//    if(operator == '|'){
  //      close(thef[0]);
    //    write(thef[1], "TESTX", 6);
      //  close(thef[1]);
      //  wait(NULL);
      //  return 0;
  //  }





    //fork
    int pid = fork();
    if(pid < 0){
        printf("fork failed\n");
    }

    //child does operations
    if(pid == 0){
        //gather directory info
        struct dirent *direct;
        DIR *dr = opendir(".");
        if (dr == NULL && pid > 0){
            printf("Could not open current directory" );
            return 0;
        }

        //if redirect, redirect output to specified file
        if(operator == '>'){
            int outfd;
            if ((outfd = open(file, O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) {
                perror(file);
                exit(1);
            }
            dup2(outfd, 1);
        }
	if(operator == '|'){
	  char val[1000000];

	  while ((direct = readdir(dr)) != NULL){
           strcat(val, direct->d_name);
	   strcat(val, "\n");
	  }
           close(thef[0]);
           write(thef[1], val, 1000000);
           close(thef[1]);
           wait(NULL);
           return 0;
         }

        //print directory contents, and then exit process
        while ((direct = readdir(dr)) != NULL)
            printf("%s\n", direct->d_name); 
        closedir(dr);
        exit(1);
    }
    //parent waits for child to finish, unless background process 
    //specified.
    if(pid > 0 && operator != '&'){
        wait(NULL);
    }
    
    return 0;
}

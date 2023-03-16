#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "cat.h"
#include "ls.h"
#include <dirent.h>
#include <signal.h>
#include <fcntl.h>
#include "pwd.h"
#include<sys/wait.h>

#define LINES 200

enum cmds {CD=0, PWD=1, LS=2, CAT=3, EXIT=4};
char *cmdstr[] = {"cd", "pwd", "ls", "cat", "exit"};

void split_up2(char* command, char** params, int* paramnum);
int execute(char** params, int paramnum);
void handler (int sig);
void handler2 (int sig);

static char line[LINES];
int volatile stop = 1;

int main(){
    char command[100];
    char* params[7];
    int paramnum = 0;
    // signal handler for control c 
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    // don't end for control c 
    if (sigaction(SIGINT, &sa, NULL) != 0){
        
    } 

    while(1){
        signal(SIGINT, handler);
        memset(line, 0, LINES);
        paramnum = 0;
        char* user = getenv("USER");
        printf("%s@shell>", user);
        fgets(command, sizeof(command), stdin);   
        if(command[strlen(command)-1] == '\n'){
            command[strlen(command)-1] = '\0';
        }	
        // this will allow the program to terminate on control d 
        if (fgets(line, LINES, stdin) == 0){
            break;
        }
        split_up2(command, params, &paramnum);
        if(execute(params, paramnum) == 1){
            break;
        }

    }
}

// handler function for signal handler 
#include <fcntl.h>
void handler (int sig){
   stop = 1;
}

void split_up2(char* command, char** params, int* paramnum){
    for(int i=0;i<7;i++){
        params[i] = strsep(&command, " ");
        if(params[i] == NULL){
            break;
        }
        (*paramnum)++;
    }
}

int execute(char** params, int paramnum){
    int ncmds = sizeof(cmdstr) / sizeof(char *);
    int i;
    //match command with one out of the list
    for(i=0;i<ncmds;i++){
        if(strcmp(params[0], cmdstr[i]) == 0){
            break;
        }
    }
    switch(i){
        case CD:
            //more than 2 arguments
            if(paramnum > 2){
                printf("too many arguments\n");
                break;
            }

            //change directory, or print error if directory not available
            if(chdir(params[1]) < 0){
                fprintf(stderr, "cannot cd %s\n", params[1]);
            }
            break;
        case PWD:
            //regular pwd command. No redirect
            if(paramnum < 2){
                pwd(' ', " ");
                break;
            
            // redirect symbol, and has three arguments, redirect the
            // output to the specified file
            }else if(strcmp(params[1], ">") == 0 && paramnum == 3){
                pwd('>', params[2]);
                break;
            }
            printf("too many arguments\n");
            break;
        case LS:
            //regular ls command with no arguments
            if(paramnum == 1){
                ls(' ', " ");
                break;

            //ls with redirect. Has symbol as argument, and arguments total to three
            }else if(strcmp(params[1], ">") == 0 && paramnum == 3){
                ls('>', params[2]);
                break;

            //run process in background
            }else if(strcmp(params[1], "&") == 0 && paramnum == 2){
                ls('&', " ");
                break;
            }      
            printf("too many arguments\n"); 
            break;
        case CAT:      
            //regular cat command, with just file as argument  
            if(paramnum<3){
                cat(params[1], ' ', " ");
                break;

            //cat command with output redirect. redirect symbol, and the two files as arguments
            }else if(strcmp(params[2], ">") == 0){
                cat(params[1], '>', params[3]);
                break;
            }

            //cat command with input redirect. redirect symbol, and file contents
            //to use as argument.
            if(strcmp(params[1], "<") == 0){
                cat(params[1], '<', params[2]);
                break;
            }

            //run process in background
            if(strcmp(params[2], "&") == 0){
                cat(params[1], '&', " ");
                break;
            }

            printf("too many arguments\n");
            break;
        case EXIT:
            printf("exiting...\n");
            //return 1 to signal loop to break
            return 1;
        
    }
    return 0;
}



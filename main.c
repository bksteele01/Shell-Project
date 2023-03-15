#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "cat.h"
#include "ls.h"
#include <dirent.h>
#include <signal.h>
#include <fcntl.h>

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
void handler (int sig){#include <fcntl.h>
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

    for(i=0;i<ncmds;i++){
        if(strcmp(params[0], cmdstr[i]) == 0){
            break;
        }
    }
    switch(i){
        case CD:
            printf("you selected cd\n"); 
            if(paramnum > 2){
                printf("too many arguments\n");
                break;
            }
            if(chdir(params[1]) < 0){
                fprintf(stderr, "cannot cd %s\n", params[1]);
            }
            break;
        case PWD:
            printf("you selected pwd\n");
            char path[200];
	    // get the current directory path and print it 
            getcwd(path, 200);
            printf("%s\n", path);
            break;
        case LS:
            printf("you selected ls\n");
            if(paramnum == 1){
                ls();
            }
            
            break;
        case CAT:
            printf("you selected cat\n");
            if(paramnum<3){
                cat(params[1], ' ', " ");
            }else if(strcmp(params[2], "<") == 0){
                cat(params[1], '<', params[3]);
            }else if(strcmp(params[2], ">") == 0){
                cat(params[1], '>', params[3]);
            }
        case EXIT:
            printf("exiting...\n");
            return 1;
    }
    return 0;
    
}



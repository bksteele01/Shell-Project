#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

enum cmds {CD=0, PWD=1};
char *cmdstr[] = {"cd", "pwd"};

void split_up2(char* command, char** params, int* paramnum);
int execute(char** params, int paramnum);

int main(){
    char command[100];
    char* params[7];
    int paramnum = 0;
    while(1){
        paramnum = 0;
        char* user = getenv("USER");
        printf("%s@shell>", user);
        fgets(command, sizeof(command), stdin);   
        if(command[strlen(command)-1] == '\n') command[strlen(command)-1] = '\0';   
        split_up2(command, params, &paramnum);
        execute(params, paramnum);

    }
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
            break;
        case PWD:
            printf("you selected pwd\n");
            break;
    }
}



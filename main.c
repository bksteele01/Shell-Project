#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void split_up2(char* command, char** params, int* paramnum);
int main(){
    char command[100];
    char* params[7];
    int paramnum = 0;
    while(1){
        paramnum = 0;
        char* user = getenv("USER");
        printf("%s@shell>", user);
        fgets(command, sizeof(command), stdin);      
        split_up2(command, params, &paramnum);
        for(int i=0;i<paramnum;i++){
            printf("%s\n", params[i]);
        }
        printf("%d\n", paramnum);

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



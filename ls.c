#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

int ls(){
    struct dirent *direct;
    DIR *dr = opendir(".");
    if (dr == NULL)
    {
        printf("Could not open current directory" );
        return 0;
    }
    while ((direct = readdir(dr)) != NULL)
        printf("%s\n", direct->d_name);

    closedir(dr);
    return 0;
}

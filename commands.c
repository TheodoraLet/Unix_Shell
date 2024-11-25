#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>


void echo(char** str,int len)
{
    for(int i=0;i<len;i++)
    printf("%s ",str[i]);

    printf("\n");
    return;
}

void touch(char** str,int len)
{
    FILE* file;

    file=fopen(str[0],"w");

    fclose(file);

}

void pwd(char** str, int len)
{
    int max_size=100;
    char buffer[max_size];

    char* cwd=getcwd(buffer,max_size);

    printf("%s\n",cwd);

    return ;
}

void ls(char** str,int len)
{
    struct dirent* dp;
    int max_size=100;
    char buffer[max_size];

    char* path=getcwd(buffer,max_size);
    strcat(path,"/");

    DIR* dir=opendir(path);
    while(dp=readdir(dir))
    {

        printf("%s ",dp->d_name);
    }
    closedir(dir);

    printf("\n");
    
    return;
}

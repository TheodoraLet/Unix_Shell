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
    int max_size=50;
    char* cwd=(char*)calloc(sizeof(char),max_size);
    if(cwd==NULL)
    printf("cwd is NULL");

    cwd=getcwd(cwd,max_size);
    if(cwd==NULL)
    printf("cwd is NULL");

    printf("%s\n",cwd);

    free(cwd);
    return ;
}

void ls(char** str,int len)
{
    struct dirent* dp;
    int max_size=50;
    char* path=(char*)malloc(sizeof(char)*max_size);

    path=getcwd(path,max_size);
    strcat(path,"/");

    DIR* dir=opendir(path);
    while(dp=readdir(dir))
    {

        printf("%s ",dp->d_name);
    }
    int c=closedir(dir);

    printf("%d\n",c);
    free(path);
    
    return;
}


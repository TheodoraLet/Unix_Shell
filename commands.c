#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>


char cd_ar[100];

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

    if(cd_ar[0]=='\0')
    file=fopen(str[0],"w");

    else{
        int max_size=100;
        char buffer[max_size];

        char* cwd=getcwd(buffer,max_size);
        strcat(cwd,"/");
        strcat(cwd,cd_ar);
        strcat(cwd,str[0]);
        file=fopen(cwd,"w");
    }

    fclose(file);

}

void pwd(char** str, int len)
{
    int max_size=100;
    char buffer[max_size];
    char* cwd=getcwd(buffer,max_size);

    if(cd_ar[0]!='\0')
    {
        strcat(cwd,"/");
        strcat(cwd,cd_ar);
        int len=strlen(cwd);
        cwd[len-1]='\0';
    }

    printf("%s\n",cwd);
    //free(cwd);

    return ;
}

void ls(char** str,int len)
{
    struct dirent* dp;
    int max_size=100;
    char buffer[max_size];

    char* path=getcwd(buffer,max_size);
    strcat(path,"/");

    if(cd_ar[0]!='\0')
    {
        strcat(path,cd_ar);
    }

    DIR* dir=opendir(path);
    while(dp=readdir(dir))
    {

        printf("%s ",dp->d_name);
    }
    closedir(dir);
    //free(path);

    printf("\n");
    
    return;
}


void cd(char** str,int len)
{
    if(str[0][0]!='.')
    {
        strcpy(cd_ar,str[0]);
    }else
    {
        for(int i=0;i<100;i++)
        cd_ar[i]='\0';
    }


    return ;
}
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <ctype.h>


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
    char* temp=(char*)malloc(sizeof(char)*100);
    strcpy(temp,cd_ar);
    strcat(temp,str[0]);
    file=fopen(temp,"w");

    fclose(file);

    free(temp);

    return;
}

void pwd(char** str, int len)
{ 
    //int l=strlen(cd_ar);
    //char* temp=(char*)malloc(sizeof(char)*l);
    //strcpy(temp,cd_ar);
    //temp[l-1]='\0';
    printf("%s\n",cd_ar);
    //free(temp);

    return ;
}

void ls(char** str,int len)
{
    struct dirent* dp;
    DIR* dir=opendir(cd_ar);
    if(!dir)
    printf("could not open dir\n");

    while(dp=readdir(dir))
    {
        printf("%s ",dp->d_name);
    }
    closedir(dir);

    printf("\n");
    
    return;
}


void cd(char** str,int len)
{
    if(str==NULL)
    {
        const char* temp=getenv("HOME");
        if(!temp)
        {
            temp=getpwuid(getuid())->pw_dir;
            printf("got inside getpwuid\n");
        }
        
        strcpy(cd_ar,temp);
        strcat(cd_ar,"/");

    }else if(strcmp(str[0],"..")==0)
    {
        int l=strlen(cd_ar);
        int j=l-2;
        while(j>=0)
        {
            if(cd_ar[j]=='/')
            {
                cd_ar[j+1]='\0';
                break;
            }

            j--;
        }

    }else if(str[0][0]=='/')
    {
        strcpy(cd_ar,str[0]);

    }else if(str[0][0]=='.')
    {
        strcat(cd_ar,str[0]+2);

    }else if(str[0][0]=='~')
    {
        const char* temp=getenv("HOME");
        if(!temp)
        {
            temp=getpwuid(getuid())->pw_dir;
        }

        strcpy(cd_ar,temp);
        strcat(cd_ar,str[0]+1);

    }else if(isalnum(str[0][0])==8){
        strcat(cd_ar,str[0]);
    }

    return ;
}

void get_initial_path()
{
    int max_size=50;
    char* path=(char*)malloc(sizeof(char)*max_size);

    path=getcwd(path,max_size);
    strcpy(cd_ar,path);
    strcat(cd_ar,"/");
    free(path);
    path=NULL;

    return;
}
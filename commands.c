#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <pwd.h>


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
    int l=strlen(cd_ar);
    char* temp=(char*)malloc(sizeof(char)*l);
    strcpy(temp,cd_ar);
    temp[l-1]='\0';
    printf("%s\n",temp);
    free(temp);

    return ;
}

void ls(char** str,int len)
{
    struct dirent* dp;
    DIR* dir=opendir(cd_ar);
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

    if(str[0][0]!='.')
    {
        strcat(cd_ar,str[0]);
    }else
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

    return;
}

void return_suffix(char* path2,char* str);

void cp(char** str,int len)
{
    FILE* file;
    FILE* file2;
    bool case1=false;
    char* path1=(char*)malloc(sizeof(char)*100);

    if(str[0][0]=='/')
    {
        case1=true;
        printf("1\n");
        file=fopen(str[0],"r");
        if(!file)
        printf("file 1 is NULL\n");
    }else if((isalnum(str[0][0])==8) || (str[0][0]=='.'))
    {
        //printf("got inside the second if\n");
        //printf("cd ar is: %s\n",cd_ar);
        strcpy(path1,cd_ar);
        if(str[0][0]=='.')
        {
            strcat(path1,str[0]+2);
        }else{
            strcat(path1,str[0]);
        }
        
    }else if(str[0][0]=='~')
    {
        const char* temp=getenv("HOME");
        if(!temp)
        {
            temp=getpwuid(getuid())->pw_dir;
        }
        strcpy(path1,temp);
        strcat(path1,str[0]+1);
    }else{
        printf("wrong source path is provided\n");
    }

    if(!case1)
    {
        printf("path1 is : %s\n",path1);
        file=fopen(path1,"r");
        if(!file)
        printf("file 1 is NULL\n");
    }

    ///////////////////////////////////////////////////////

    char* path2=(char*)malloc(sizeof(char)*100);
    int l=strlen(str[1]);
    if(str[1][0]=='/')
    {
        strcpy(path2,str[1]);
        if(str[1][l-1]=='/')
        {
            return_suffix(path2,str[0]);
        }

    }else if((isalnum(str[1][0])==8) || (str[1][0]=='.') )
    {
        strcpy(path2,cd_ar);
        if(str[1][0]=='.')
        {
            strcat(path2,str[1]+2);
        }else{
            strcat(path2,str[1]);
        }
        if(str[1][l-1]=='/')
        {
            return_suffix(path2,str[0]);
        }
        
    }else if(str[1][0]=='~')
    {
        const char* temp2=getenv("HOME");
        if(!temp2)
        {
            temp2=getpwuid(getuid())->pw_dir;
            printf("got inside getpwuid\n");
        }
        strcpy(path2,temp2);
        strcat(path2,str[1]+1);
        int l=strlen(str[1]);
        if(str[1][l-1]=='/')
        {
            return_suffix(path2,str[0]);
        }

    }else{
        printf("wrong destination path is provided\n");
    }

    if(path2)
    {
        printf("path2 is : %s\n",path2);
        file2=fopen(path2,"w");
        if(!file2)
        printf("file 2 is NULL\n");
    }

    int c;
    while((c=fgetc(file))!=EOF)
    {
        fputc(c,file2);
    }

    int c1= fclose(file);
    int c2=fclose(file2);
    printf("c1 is %d , c2 is %d\n",c1,c2);
    free(path2);
    free(path1);
    

    return;
}

void return_suffix(char* path2,char* str)
{
    int l1=strlen(str);
    char* temp=(char*)malloc(sizeof(char)*100);
    //printf("1\n");
    char* token=strtok(str,"/");
    while(token!=NULL)
    {
        strcpy(temp,token);
        token=strtok(NULL,"/");
    }
    strcat(path2,temp);
    free(temp);
}

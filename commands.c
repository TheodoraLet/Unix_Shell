#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
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

void cp(char** str,int len)
{
    FILE* file;
    FILE* file2;
    bool flag_path1=false;
    char* path1=(char*)malloc(sizeof(char)*100);

    if(str[0][0]=='/')
    {
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
        printf("path1 is :");
        printf("%s\n",path1);
        file=fopen(path1,"r");
        if(!file)
        printf("file 1 is NULL\n");
        flag_path1=true;
    }else{
        printf("wrong source path is provided\n");
        // printf("the first element is: %c\n",str[0][0]);
        // printf("%d\n",isalnum(str[0][0]));
    }

    ///////////////////////////////////////////////////////

    char* path2=(char*)malloc(sizeof(char)*100);
    int l=strlen(str[1]);
    if(str[1][0]=='/')
    {
        strcpy(path2,str[1]);
        if(str[1][l-1]=='/')
        {
            int l1=strlen(str[0]);
            char* temp=(char*)malloc(sizeof(char)*100);
            printf("1\n");
            char* token=strtok(str[0],"/");
            while(token!=NULL)
            {
                strcpy(temp,token);
                token=strtok(NULL,"/");
            }
            strcat(path2,temp);
            free(temp);
        }

        file2=fopen(path2,"w");
        if(!file2)
        printf("file 2 is NULL\n");

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
            //printf("got in the / if\n");
            int l1=strlen(str[0]);
            char* temp=(char*)malloc(sizeof(char)*100);
            char* token=strtok(str[0],"/");
            while(token!=NULL)
            {
                strcpy(temp,token);
                token=strtok(NULL,"/");
            }
            strcat(path2,temp);
        }
        printf("path2 is :");
        printf("%s\n",path2);
        file2=fopen(path2,"w");
        if(!file2)
        printf("file2 is NULL\n");
    }else{
        printf("wrong destination path is provided\n");
    }

    int c;
    while((c=fgetc(file))!=EOF)
    {
        fputc(c,file2);
    }

    fclose(file);
    fclose(file2);
    free(path2);
    if(flag_path1) free(path1);
    

    return;
}
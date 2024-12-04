#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <pwd.h>
#include <sys/stat.h>
#include <errno.h>


char cd_ar[100];

char* home_path(char* arg);
char* relative_path(char* arg);
char* return_parent_path(char* str);
bool startsWith(char* haystack, char* needle);

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

    char* path;
    for(int i=0;i<len;i++)
    {
        if(str[i][0]=='~')
        {   
            path=home_path(str[i]);
            printf("path is %s\n",path);
            file=fopen(path,"w");
            int c=fclose(file);
            free(path);
            
            if(c)
            printf("an error occured\n");

        }else if(startsWith(str[i],"../"))
        {
            path=return_parent_path(str[i]);
            printf("path is %s\n",path);
            file=fopen(path,"w");
            int c=fclose(file);
            free(path);
            
            if(c)
            printf("an error occured\n");

        }else if(isalnum(str[i][0])==8 || str[i][0]=='.')
        {

            path=relative_path(str[i]);
            printf("path is %s\n",path);
            file=fopen(path,"w");
            int c=fclose(file);
            free(path);
            
            if(c)
            printf("an error occured\n");

        }else if(str[i][0]=='/'){
            printf("path is %s\n",str[i]);
            file=fopen(str[i],"w");
            int c=fclose(file);

            if(c)
            printf("an error occured\n");

        }else{
            printf("did not find the file\n");
        }
    }

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
    if(len==0)
    {
        //printf("got inside if\n");
        const char* temp=getenv("HOME");
        if(!temp)
        {
            temp=getpwuid(getuid())->pw_dir;
            printf("got inside getpwuid\n");
        }
        
        memcpy(cd_ar,temp,strlen(temp)+1);
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
    }else{
        printf("the path provided is not found\n");
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

void return_suffix(char* path2,char* str);

void cp(char** str,int len)
{
    FILE* file;
    FILE* file2;
    char* path;
    bool case1=false;

    if(str[0][0]=='/')
    {
        case1=true;
        printf("1\n");
        file=fopen(str[0],"r");
        if(!file)
        printf("file 1 is NULL\n");

    }else if(startsWith(str[0],"../"))
    {
        path=return_parent_path(str[0]);
        printf("path is %s\n",path);

    }else if((isalnum(str[0][0])==8) || (str[0][0]=='.'))
    {
        path=relative_path(str[0]);
        printf("path is %s\n",path);
        
    }else if(str[0][0]=='~')
    {
        path=home_path(str[0]);
        printf("path is %s\n",path);

    }else{
        printf("wrong source path is provided\n");
        return;
    }

    if(!case1)
    {
        printf("path1 is : %s\n",path);
        file=fopen(path,"r");
        if(!file)
        printf("file 1 is NULL\n");
    }

    ///////////////////////////////////////////////////////

    char* path2;
    int l=strlen(str[1]);
    if(str[1][0]=='/')
    {
        path2=(char*)malloc(sizeof(char)*(strlen(str[0])+strlen(str[1])+1));
        strcpy(path2,str[1]);
        if(str[1][l-1]=='/')
        {
            return_suffix(path2,str[0]);
        }

    }else if(startsWith(str[1],"../"))
    {
        path2=return_parent_path(str[1]);

        if(str[1][l-1]=='/')
        {
            path2=realloc(path2,strlen(path2)+strlen(str[0])+1);
            return_suffix(path2,str[0]);
        }

    }else if((isalnum(str[1][0])==8) || (str[1][0]=='.') )
    {
        path2=relative_path(str[1]);

        if(str[1][l-1]=='/')
        {
            path2=realloc(path2,strlen(path2)+strlen(str[0])+1);
            return_suffix(path2,str[0]);
        }
        
    }else if(str[1][0]=='~')
    {
        path2=home_path(str[1]);

        if(str[1][l-1]=='/')
        {
            int max_size_of_home_dir=20;
            path2=realloc(path2,strlen(path2)+strlen(str[0])+1);
            return_suffix(path2,str[0]);
        }

    }else{
        printf("wrong destination path is provided\n");
        return;
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
    //printf("c1 is %d , c2 is %d\n",c1,c2);
    free(path2);
    if(!case1) free(path);
    

    return;
}

void return_suffix(char* path2,char* str)
{
    int l1=strlen(str);
    char* temp=(char*)malloc(sizeof(char)*(strlen(str)+1));
    //printf("1\n");
    char* token=strtok(str,"/");
    while(token!=NULL)
    {
        strcpy(temp,token);
        token=strtok(NULL,"/");
    }
    strcat(path2,temp);
    free(temp);
    temp=NULL;

    return;
}


void rm(char** str,int len)
{
    printf("len is %d\n",len);
    for(int i=0;i<len;i++)
    {
        if(str[i][0]=='~')
        {   
            char* path=home_path(str[i]);
            int c=unlink(path);
            free(path);

            if(c!=0)
            printf("an error occured\n");

        }else if(startsWith(str[i],"../"))
        {
            char* path=return_parent_path(str[i]);
            int c=unlink(path);
            free(path);

            if(c!=0)
            printf("an error occured\n");

        }else if(isalnum(str[i][0])==8 || str[i][0]=='.')
        {
            char* path=relative_path(str[i]);
            int c=unlink(path);
            free(path);

            if(c!=0)
            printf("an error occured\n");

        }else if(str[i][0]=='/'){
            char temp[strlen(str[i])+1];
            strcpy(temp,str[i]);
            int c=unlink(temp);

            if(c!=0)
            printf("an error occured\n");

        }else{
            printf("did not find the file\n");
        }
    }

    return ;
}


void mkdir_m(char** str, int len)
{
    for(int i=0;i<len;i++)
    {
        if(str[i][0]=='~')
        {   
            char* path=home_path(str[i]);
            printf("path is %s\n",path);

            int c=mkdir(path,S_IRWXU | S_IRWXG | S_IRWXO);

            free(path);

            if(c==-1)
            printf("Error: %s\n",strerror(errno));

        }else if(startsWith(str[i],"../"))
        {
            char* path=return_parent_path(str[i]);
            printf("path is %s\n",path);

            int c=mkdir(path,S_IRWXU | S_IRWXG | S_IRWXO);
            free(path);

            if(c==-1)
            printf("Error: %s\n",strerror(errno));


        }else if(isalnum(str[i][0])==8 || str[i][0]=='.')
        {
            char* path=relative_path(str[i]);
            printf("path is %s\n",path);

            int c=mkdir(path,S_IRWXU | S_IRWXG | S_IRWXO);
            free(path);

            if(c==-1)
            printf("Error: %s\n",strerror(errno));

        }else if(str[i][0]=='/'){
            char temp[strlen(str[i])+1];
            strcpy(temp,str[i]);
            int c=mkdir(temp,S_IRWXU | S_IRWXG | S_IRWXO);

            if(c==-1)
            printf("Error: %s\n",strerror(errno));

        }else{
            printf("did not understand the path\n");
        }
    }

    return ;
}

char* home_path(char* arg)
{
    const char* temp=getenv("HOME");
    if(!temp)
    {
        temp=getpwuid(getuid())->pw_dir;
    }
    char* path=(char*)malloc(sizeof(char)* (strlen(temp)+strlen(arg)+1));
    memcpy(path,temp,strlen(temp)+1);
    strcat(path,arg+1);

    return path;
}

char* relative_path(char* arg)
{
    char* path=(char*)malloc(sizeof(char)* (strlen(cd_ar)+strlen(arg)+1));
    memcpy(path,cd_ar,strlen(cd_ar)+1);
    if(arg[0]=='.')
    {
        strcat(path,arg+2);
    }else{
        strcat(path,arg);
    }

    return path;
}


void whoami(char** str, int len)
{
    char* temp=getlogin();

    if(temp)
    {
        printf("%s\n",temp);
    }else{
        printf("Error: %s\n",strerror(errno));
    }
}

char* return_name(char* str);

void wc(char** str, int len)
{
    FILE* file;
    char* path;
    for(int i=0;i<len;i++)
    {
        if(str[i][0]=='~')
        {   
            path=home_path(str[i]);
            //printf("path is %s\n",path);

        }else if(startsWith(str[i],"../"))
        {
            path=return_parent_path(str[i]);
            
        }else if(isalnum(str[i][0])==8 || str[i][0]=='.')
        {
            path=relative_path(str[i]);
            //printf("path is %s\n",path);


        }else if(str[i][0]=='/'){
            path=(char*)malloc(sizeof(char)*(strlen(str[i])+1));
            strcpy(path,str[i]);

        }else{
            printf("did not understand the path\n");
            return;
        }

        file=fopen(path,"r");
        
        if(!file) printf("file is NULL\n"); 

        int count=0; int word=0; char ch; int lines=0;
        while((ch=fgetc(file))!=EOF)
        {
            if(ch==' ' || ch=='\n')
            {
                word=0;
                if(ch=='\n')
                lines++;

            }else{
                if(!word)
                {
                    count++;
                    word=1;
                }
            }
        }
        int c=fclose(file);

        if(c!=0)
        printf("Error : %s\n",strerror(errno));

        file=fopen(path,"r");
        
        if(!file) printf("file is NULL\n"); 
        fseek(file, 0L, SEEK_END); 

        long int res = ftell(file);

        c=fclose(file);
        if(c!=0)
        printf("Error : %s\n",strerror(errno));

        char* temp=return_name(str[i]);
        if(strcmp(temp,"pdf")==0)
        printf("entered a .pdf file lines and words numbers are not valid!\n");
        
        printf("%d %d %ld %s\n",lines,count,res,path);
        if(path) free(path);
        free(temp);
    }

    return;
}

char* return_name(char* str)
{
    int l1=strlen(str);
    char* temp=(char*)malloc(sizeof(char)*(strlen(str)+1));
    //printf("1\n");
    char* token=strtok(str,".");
    while(token!=NULL)
    {
        strcpy(temp,token);
        token=strtok(NULL,".");
    }

    return temp;
}

bool startsWith(char* haystack, char* needle)
{
    for(int i=0;needle[i]!='\0';i++)
    {
        if(needle[i]!=haystack[i])
        return false;
    }

    return true;
}

char* return_parent_path(char* str)
{
    int len=strlen(cd_ar);
    char* path=(char*)malloc(sizeof(char)*strlen(cd_ar)+1);
    strcpy(path,cd_ar);
    for(int i=len-2;i>=0;i--)
    {
        if(path[i]=='/')
        {
            path[i+1]='\0';
            break;
        }
    }

    path=realloc(path,sizeof(char)*(strlen(path)+strlen(str+3)+1));
    strcat(path,str+3);

    return path;
}
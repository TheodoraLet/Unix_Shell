#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <structs.h>

int max_length_of_command =100;
int max_length_of_arguments=100;

char* sh_read()
{
    char* buffer=(char*)malloc(sizeof(char) *max_length_of_command);
    int len=0;
    while(true)
    {
        int res=scanf("%c",buffer+(len));

        if(res==1)
        {
            if(buffer[len]=='\n')
            {
                buffer[len]='\0';
                return buffer;
            }else if(len==max_length_of_command-1)
            {
                max_length_of_command*=2;
                buffer=(char*)realloc(buffer,sizeof(char) *max_length_of_command);
                if(buffer==NULL)
                {
                    printf("Error! not enough space for reallocation\n");
                    return "\0";
                }else{
                    printf("Success! Reallocated memory\n");
                }

            }
            len++;
        }
    }

    free(buffer);
    return EXIT_SUCCESS;

}


arg_str* tokenize(char* str)
{
    arg_str* res=(arg_str*)malloc(sizeof(arg_str));
    res->_arg=(char**)malloc(sizeof(char*)*max_length_of_arguments);
    res->_len=0;
    char* token=strtok(str," ");
    while(token!=NULL)
    {
        if(res->_len==max_length_of_arguments-1)
        {
            max_length_of_arguments*=2;
            res->_arg=(char**)realloc(res->_arg,sizeof(char*)*max_length_of_arguments);
            if(res->_arg==NULL)
            {
                printf("Error! not enough space for reallocation\n");
                return NULL;
            }else{
                printf("Success! Reallocated memory\n");
            }
        }
        int size=strlen(token);
        res->_arg[res->_len]=(char*)malloc(sizeof(char)*size);
        res->_arg[(res->_len)++]=token;
        token=strtok(NULL," ");
    }

    return res;
}

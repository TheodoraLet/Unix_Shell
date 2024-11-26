#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <structs.h>
#include <commands.h>

int max_number_of_functions=101;
int n_of_keys=0;


int hash(const char *str, int hashmap_size) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash % hashmap_size;
}

void rehash(hashNode* ar,int* hashMapSize)
{
    hashNode* new=(hashNode*)malloc(sizeof(hashNode)*(2*(*hashMapSize)));
    for(int i=0;i<*hashMapSize;i++)
    {
        int hashIndex=hash(ar->key,2*(*hashMapSize));
        while(new[hashIndex].key!=NULL && new[hashIndex].key!=ar[hashIndex].key)
        {
            hashIndex=(hashIndex+1)%(*hashMapSize);
        }

        new[hashIndex].key=ar[hashIndex].key;
    }

    free(ar);
    ar=new;
    *hashMapSize*=2;    
}

void hashMapInsert(comm_str* comm,hashNode* ar,int* hashMapSize)
{
    double load_factor=n_of_keys/(*hashMapSize);
    if(load_factor>=0.75)
    {
        rehash(ar,hashMapSize);
    }
    int hashIndex=hash(comm->_fname,max_number_of_functions);

    while(ar[hashIndex].key!=NULL && ar[hashIndex].key!=comm->_fname)
    {
        hashIndex=(hashIndex+1)%(*hashMapSize);
    }

    ar[hashIndex].key=strdup(comm->_fname);
    ar[hashIndex].p=comm->ptr;
    //printf("hashIndex is:");
    //printf("%d\n",hashIndex);
    n_of_keys++;

}


char* hashMapSearch(arg_str* arg,hashNode* ar,int* hashMapSize)
{
    int counter=0;
    int hashIndex=hash(arg->_arg[0],*hashMapSize);


    while(counter< *hashMapSize)
    {
        if(strcmp(ar[hashIndex].key,arg->_arg[0])==0)
        {
            printf("the function to be executed is: ");
            printf("%s\n",ar[hashIndex].key);
            char* param=arg->_arg[1];
            if(param==NULL)
            {
                printf("function has null arguments\n");
                ar[hashIndex].p(NULL,0);
            }else{
                ar[hashIndex].p((arg->_arg)+1,(arg->_len)-1);
            }
            return EXIT_SUCCESS;
        }

        if(ar[hashIndex].key!=arg->_arg[0] || ar[hashIndex].key==NULL)
        hashIndex=(hashIndex+1)%(*hashMapSize);

        counter++;
    }

    return NULL;
}


comm_str* CreateCommand(char* str,void (*ptr)(char **,int ))
{
    comm_str* comm=(comm_str*)malloc(sizeof(comm_str));
    comm->_fname=strdup(str);
    comm->ptr=ptr;

    return comm;
}

void initializeHashMap(hashNode* ar)
{
    comm_str* comm=CreateCommand("echo",echo);
    
    hashMapInsert(comm,ar,&max_number_of_functions);
    free(comm);

    comm_str* comm2=CreateCommand("touch",touch);
    
    hashMapInsert(comm2,ar,&max_number_of_functions);
    free(comm2);

    comm_str* comm3=CreateCommand("pwd",pwd);
    
    hashMapInsert(comm3,ar,&max_number_of_functions);
    free(comm3);

    comm_str* comm1=CreateCommand("ls",ls);
    
    hashMapInsert(comm1,ar,&max_number_of_functions);
    free(comm1);

}
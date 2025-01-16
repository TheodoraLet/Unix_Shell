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
            hashIndex=(hashIndex+1)%(2*(*hashMapSize));
        }

        new[hashIndex].key=(char*)malloc(sizeof(char)*(strlen(ar[hashIndex].key)+1));
        memcpy(new[hashIndex].key,ar[hashIndex].key,strlen(ar[hashIndex].key)+1);
        free(ar[hashIndex].key);
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

    ar[hashIndex].key=(char*)malloc(sizeof(char)*(strlen(comm->_fname)+1));
    memcpy(ar[hashIndex].key,comm->_fname,strlen(comm->_fname)+1);
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
            //printf("the function to be executed is: ");
            //printf("%s\n",ar[hashIndex].key);
            char* param=arg->_arg[1];
            if(param==NULL)
            {
                ar[hashIndex].p((char**)NULL,0);
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
    comm->_fname=(char*)malloc(sizeof(char)*(strlen(str)+1));
    memcpy(comm->_fname,str,strlen(str)+1);
    comm->ptr=ptr;

    return comm;
}

void initializeHashMap(hashNode* ar)
{
    comm_str* comm=CreateCommand("echo",&echo);
    
    hashMapInsert(comm,ar,&max_number_of_functions);
    if(comm) free(comm->_fname); free(comm);comm=NULL; 

    comm=CreateCommand("touch",&touch);
    
    hashMapInsert(comm,ar,&max_number_of_functions);
    if(comm) free(comm->_fname);free(comm);comm=NULL;

    comm=CreateCommand("pwd",&pwd);
    
    hashMapInsert(comm,ar,&max_number_of_functions);
    if(comm) free(comm->_fname);free(comm);comm=NULL;


    comm=CreateCommand("ls",&ls);
    
    hashMapInsert(comm,ar,&max_number_of_functions);
    if(comm) free(comm->_fname);free(comm);comm=NULL;

    comm=CreateCommand("cd",&cd);
    
    hashMapInsert(comm,ar,&max_number_of_functions);
    if(comm) free(comm->_fname); free(comm);comm=NULL;
    

    comm=CreateCommand("cp",&cp);
    
    hashMapInsert(comm,ar,&max_number_of_functions);
    if(comm) free(comm->_fname);free(comm);comm=NULL;

    comm=CreateCommand("rm",&rm);
    
    hashMapInsert(comm,ar,&max_number_of_functions);
    if(comm) free(comm->_fname);free(comm);comm=NULL;

    comm=CreateCommand("mkdir_m",&mkdir_m);
    
    hashMapInsert(comm,ar,&max_number_of_functions);
    if(comm) free(comm->_fname);free(comm);comm=NULL;

    comm=CreateCommand("whoami",&whoami);
    
    hashMapInsert(comm,ar,&max_number_of_functions);
    if(comm) free(comm->_fname);free(comm);comm=NULL;

    comm=CreateCommand("wc",&wc);
    
    hashMapInsert(comm,ar,&max_number_of_functions);
    if(comm) free(comm->_fname);free(comm);comm=NULL;

}
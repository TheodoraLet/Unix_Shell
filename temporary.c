#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <commands.h>
#include <hashMap2.h>
#include <user_interface_functions.h>



int main()
{
    hashNode* ar=(hashNode*)malloc(sizeof(hashNode)*max_number_of_functions);
    initializeHashMap(ar);
    get_initial_path();

    while(1)
    {
        char* res=sh_read();
        
        arg_str* arg=tokenize(res);
    
        char* new=hashMapSearch(arg,ar,&max_number_of_functions);
        if(res) 
        {
            free(res);
            res=NULL;
        }else{
            printf("res =NULL\n");
        }

        if(arg) 
        {
            free(arg);
            arg=NULL;
        }else{
            printf("arg=NULL\n");
        }
    }
    

    return 0;
}







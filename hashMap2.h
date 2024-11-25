#include <structs.h>
#include <commands.h>

#ifndef HASHMAP2_H
#define HASHMAP2_H


extern int max_number_of_functions;
extern int n_of_keys;

int hash(const char *str, int hashmap_size);

void hashMapInsert(comm_str* comm,hashNode* ar,int* hashMapSize);

void rehash(hashNode* ar,int* hashMapSize);

char* hashMapSearch(arg_str* arg,hashNode* ar,int* hashMapSize);

void initializeHashMap(hashNode* ar);

comm_str* CreateCommand(char* str,void (*ptr)(char **,int ));


#endif
#include <structs.h>

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

extern int max_length_of_command ;
extern int max_length_of_arguments;

char* sh_read();

arg_str* tokenize(char* str);


#endif
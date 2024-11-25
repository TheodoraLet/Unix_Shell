#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct arg_str{
    char** _arg;
    int _len;
}arg_str;

typedef struct comm_str{
    char* _fname;
    void (*ptr)(char **,int );
}comm_str;

typedef struct hashNode{
    char* key;
    void (*p)(char **,int);
}hashNode;

#endif
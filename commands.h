#ifndef COMMANDS_H
#define COMMANDS_H

extern char cd_ar[];

void echo(char** str,int len);

void touch(char** str,int len);

void pwd(char** str, int len);

void ls(char** str,int len);

void cd(char** str,int len);

void get_initial_path();

void cp(char** str,int len);

void return_suffix(char* path2,char* str);

void rm(char** str,int len);

void mkdir_m(char** str, int len);

#endif
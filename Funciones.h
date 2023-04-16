#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_PATH 512

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void search_dir(char *dir_name, char *region, char *species, char *type, int nocount, int list, int size, char *name);
bool match_criteria(char* filename, char* region, char* species, char* type, char* name);

#endif
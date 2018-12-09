#ifndef BP_H_INCLUDED
#define BP_H_INCLUDED

#include <time.h>
#include <errno.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include "char.h"
#define breakline printf("\n");
#define TXT_TYPE 0
#define DATA_TYPE 1
#define NODE_TYPE 2


typedef struct data Data;


bool print_data(FILE* f, int pos, int limit);
int search(FILE* f, int degree, int key, int root, int op);
void rangeSearch(FILE* f, int degree, int root, int key, int end, int op);

typedef struct data{
    int key;
    char name[29];
    long int city_code;
    char UF[3];
    double area;
}Data;


#endif // BP_H_INCLUDED

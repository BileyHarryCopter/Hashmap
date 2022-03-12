#ifndef HASH
#define HASH

#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define CRIT_KOEF 0.6
#define ENCR_KOEF 2

enum
{
    NO_ERROR    = 0,
    INPUT_ERROR = 1,
    FSTDIO      = 2,
    FFILE       = 3,
    SIZE_INIT   = 10,
    STRLEN      = 50
};

typedef char* data_t;
struct node_t;
typedef struct hashmap hashmap;

//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
hashmap *Hash_Ctor (const unsigned size_init, unsigned (*Hash_Calc)(data_t data));
int Hash_Resz (hashmap *hshmp);
int Hash_Dtor (hashmap *hshmp);
unsigned Hash_Find (hashmap hshmp, data_t data);

int Hash_Fill (int mode, ...);

int Hash_Insrt (hashmap *hshmp, data_t insrt_data);


// int Contest_Task (hashmap hshmp, const char* name);
int Contest_Task (hashmap *hshmp);


void Hash_Dump (hashmap *hshmp);
unsigned Hash_Calc (data_t data);

char *strctor  (char first);
char *fstrctor (char first, FILE * file);
int istrcmp (const char * str1, const char * str2);

#endif

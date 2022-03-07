#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#define CRIT_KOEF 0.6
#define ENCR_KOEF 2

enum
{
    NO_ERROR   = 0,
    FILE_ERROR = 1,
    SIZE_INIT  = 10,
    STRLEN     = 50
};

typedef const char* data_t;

typedef struct node_t
{
    struct node_t *next;
    data_t        data;
} node_t;

typedef struct bucket
{
    node_t        *top;
} bucket;

typedef struct hashmap
{
    bucket        *array;
    unsigned      capacity;
    unsigned      insertion;
    unsigned      (*hash_calc) (data_t data);
} hashmap;

//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int Hash_Ctor (hashmap *hshmp, unsigned size_init, unsigned (*Hash_Calc)(data_t data));
int Hash_Resz (hashmap *hshmp);
int Hash_Dtor (hashmap *hshmp);
unsigned Hash_Find (hashmap hshmp, data_t data);
int Hash_Fill (hashmap *hshmp, const char *fname);
int Hash_Insrt (hashmap *hshmp, data_t insrt_data);
int Contest_Task (hashmap hshmp, const char* name);
void Hash_Dump (hashmap hshmp);
unsigned Hash_Calc (data_t data);

char *strctor (char first, FILE * file);
int istrcmp (const char * str1, const char * str2);

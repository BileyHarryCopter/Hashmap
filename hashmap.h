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
    ERROR,
    INPUT_ERROR,
    CONTEST,
    FFILE,
    SIZE_INIT   = 100,
    STRLEN      = 50
};

typedef char* data_t;
typedef struct list_t list_t;
typedef struct hashmap hashmap;

//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
hashmap *HashCtor (const unsigned size_init, unsigned (*hashcalc)(data_t data));
int HashResz (hashmap *hshmp);
int HashDtor (hashmap *hshmp);
unsigned HashFind (const hashmap *hshmp, data_t data);

int HashFill (int mode, ...);

int HashInsrt (hashmap *hshmp, data_t insrt_data);


// int Contest_Task (hashmap hshmp, const char* name);
int ContestTask (hashmap *hshmp);


void HashDump (hashmap *hshmp);
unsigned HashCalc (data_t data);

int strdel (char * str);
char *strctor  (char first);
char *fstrctor (char first, FILE * file);
int istrcmp (const char * str1, const char * str2);

#endif

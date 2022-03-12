#include "hashmap.h"
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
              //   Announcement the structer of hashmap    //
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
typedef struct node_t
{
    struct node_t *next;
    data_t        data;
} node_t;

typedef struct bucket
{
    node_t        *top;
} bucket;

struct hashmap
{
    bucket        *array;
    unsigned      capacity;
    unsigned      insertion;
    unsigned      (*hash_calc) (data_t data);
};
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
hashmap *Hash_Ctor (unsigned size_init, unsigned (*Hash_Calc)(data_t data))
{
    int i = 0;
    hashmap *hshmp = (hashmap *)calloc (1, sizeof (hashmap));

    hshmp->capacity    = size_init;
    hshmp->insertion   = 0;
    hshmp->array       = (bucket*) calloc (size_init, sizeof (bucket));
    for (i = 0; i < size_init; i++)
    {
        hshmp->array[i].top = (node_t *) calloc (1, sizeof (node_t));
    }
    (hshmp->hash_calc) = Hash_Calc;

    return hshmp;
}

int Hash_Fill (int mode, ...)
{
    va_list args;

    char symb;
    char *str;
    char *fname;
    hashmap *hshmp;
    unsigned  find_numb;
    unsigned  size_buff;
    unsigned  stri_numb;
    unsigned   position;

    va_start (args, mode);
    hshmp = va_arg (args, hashmap*);
    assert (hshmp);

    if (mode == FSTDIO)
    {
        scanf ("%u %u", &find_numb, &size_buff);
        while (getchar () != '\n') {;}
        for (position = 0; position < size_buff; position++)
        {
            symb = getchar ();
            if (isalpha (symb))
            {
                str = strctor (symb);
                position += strlen (str);
                Hash_Insrt (hshmp, str);
            }
        }
    }
    else if (mode == FFILE)
    {
        fname = va_arg (args, char*);
        FILE *file = fopen (fname, "r");
        if (!file)
            return INPUT_ERROR;
        fseek (file, 0L, SEEK_SET);
        assert (fscanf (file ,"%u %u", &find_numb, &size_buff) == 2);
        while (fgetc (file) != '\n') {;}
        for (position = 0; position < size_buff; position++)
        {
            symb = fgetc (file);
            if (isalpha (symb) != 0)
            {
                str = fstrctor (symb, file);
                position += strlen (str);
                Hash_Insrt (hshmp, str);
            }
        }
        fclose (file);
    }
    else
        return INPUT_ERROR;

    va_end (args);
    return NO_ERROR;
}

unsigned Hash_Find (hashmap hshmp, data_t data)
{
    assert (&hshmp);
    unsigned key = (*hshmp.hash_calc)(data) % (hshmp.capacity);
    unsigned conv, pos = 0;
    node_t *list = hshmp.array[key].top;

    if (!(list->next))
        return 0;
    else
    {
        conv = 0;
        list = list->next;
        while (list->next != NULL)
        {
            if (!istrcmp (list->data, data))
                conv++;
            list = list->next;
        }
        if (!istrcmp (list->data, data))
            conv++;
    }

    return conv;
}

int Contest_Task (hashmap *hshmp)
{
    char symb;
    char *str;
    unsigned   position;
    unsigned   size_buff = 0;

    scanf ("%u", &size_buff);
    while (getchar () != '\n') {;}

    for (position = 0; position < size_buff; position++)
    {
        symb = getchar ();
        if (isalpha (symb))
        {
            str = strctor (symb);
            printf ("%u ", Hash_Find (*hshmp, str));
            position += strlen (str);
        }
    }
    printf ("\n");
    return NO_ERROR;
}

unsigned Hash_Calc (data_t data)
{
    unsigned hash_key = 5381;
    while (*data != '\0')
    {
        hash_key = ((hash_key << 5) + hash_key) + *data;
        data++;
    }
    return hash_key;
}

int Hash_Insrt (hashmap *hshmp, data_t insrt_data)
{
    unsigned hash_key = 0;
    node_t   *list    = (node_t *) calloc (1, sizeof (node_t));

    if (hshmp->insertion > CRIT_KOEF * hshmp->capacity)
        Hash_Resz (hshmp);
    hash_key = (*hshmp->hash_calc)(insrt_data) % (hshmp->capacity);

    assert (hshmp->array[hash_key].top);

    if (hshmp->array[hash_key].top == NULL)
    {
        hshmp->array[hash_key].top->next = (node_t *) calloc (1, sizeof (node_t));
    }

    list->next = hshmp->array[hash_key].top->next;
    list->data = insrt_data;
    hshmp->array[hash_key].top->next = list;

    hshmp->insertion += 1;
    return NO_ERROR;
}

int Hash_Resz (hashmap *hshmp)
{
    unsigned i = 0;
    node_t *first, *second;
    hashmap *new_hshmp = (hashmap *) calloc (1, sizeof (hashmap));

    new_hshmp = Hash_Ctor (ENCR_KOEF * hshmp->capacity, hshmp->hash_calc);

    for (i = 0; i < hshmp->capacity; i++)
    {
        first = hshmp->array[i].top;
        if (first->next == NULL)
        {
            free (first);
            continue;
        }
        first = first->next;
        while (first->next != NULL)
        {
            Hash_Insrt (new_hshmp, first->data);
            second = first;
            first = first->next;
            free (second);
        }
        Hash_Insrt (new_hshmp, first->data);
        free (first);
    }

    free (hshmp->array);
    hshmp->array     = new_hshmp->array;
    hshmp->capacity  = new_hshmp->capacity;
    hshmp->insertion = new_hshmp->insertion;
    hshmp            = new_hshmp;

    return NO_ERROR;
}

int Hash_Dtor (hashmap *hshmp)
{
    int i = 0;
    node_t *first  = NULL;
    node_t *second = NULL;

    assert (hshmp);

    for (i = 0; i < hshmp->capacity; i++)
    {
        first = hshmp->array[i].top;
        assert (first);
        while (first->next != NULL)
        {
            second = first;
            first  = first->next;
            free (second);
        }
    }

    free (hshmp->array);

    return NO_ERROR;
}

void Hash_Dump (hashmap *hshmp)
{
    int i = 0;
    node_t *list;

    printf ("_HASHMAP_\n");
    printf ("\tCAPACITY:   %u\n", hshmp->capacity);
    printf ("\tINSERTIONS: %u\n\n", hshmp->insertion);
    for (i = 0; i < hshmp->capacity; i++)
    {
        printf ("bucket[%d]:\n\t", i);
        list = hshmp->array[i].top;
        while (list)
        {
            printf ("%s -> ", list->data);
            list = list->next;
        }
        printf ("%p", list);
        printf ("\n");
    }
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
char *fstrctor (char first, FILE * file)
{
    unsigned length = 0;
    char *str = (char *) calloc (STRLEN, sizeof (char));
    *(str + length) = first;
    while (isalpha (*(str + length)) != 0)
    {
        length++;
        *(str + length) = fgetc (file);
    }
    *(str + length) = '\0';
    return str;
}

char *strctor (char first)
{
    unsigned length = 0;
    char *str = (char *) calloc (STRLEN, sizeof (char));
    *(str + length) = first;
    while (isalpha (*(str + length)) != 0)
    {
        length++;
        *(str + length) = getchar ();
    }
    *(str + length) = '\0';
    return str;
}

int istrcmp (const char * str1, const char * str2)
{
    while (isalpha (*str1) != 0)
    {
        if (tolower (*str1) != tolower (*str2))
        {
            return (*str1 - *str2);
        }
        str1++;
        str2++;
    }
    return (*str1 == ' ' || *str1 == '\t' || *str1 == '\n' || *str1 == '\0') ? 0 : -1;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//

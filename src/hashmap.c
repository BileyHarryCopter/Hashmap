#include "hashmap.h"
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
              //   Announcement the structer of hashmap    //
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
struct list_t
{
    struct list_t *next;
    data_t         data;
};

struct hashmap
{
    list_t        **array;
    unsigned      capacity;
    unsigned      insertion;
    unsigned      (*hashcalc) (data_t data);
};
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
hashmap *HashCtor (const unsigned size_init, unsigned (*hashcalc)(data_t data))
{
    int i = 0;
    hashmap *hshmp = (hashmap *) calloc (1, sizeof (hashmap));

    hshmp->capacity    = size_init;
    hshmp->insertion   = 0;
    hshmp->array       = (list_t **) calloc (size_init, sizeof (list_t *));
    hshmp->hashcalc = HashCalc;

    return hshmp;
}

int HashFill (int mode, ...)
{
    va_list        args;

    char           symb;
    char           *str;
    char         *fname;
    hashmap      *hshmp;
    unsigned  find_numb;
    unsigned  size_buff;
    unsigned  stri_numb;
    unsigned   position;

    va_start (args, mode);
    hshmp = va_arg (args, hashmap*);
    assert (hshmp);

    if (mode == CONTEST)
    {
        scanf ("%u %u", &find_numb, &size_buff);
        while (getchar () != '\n') {;}
        for (position = 0; position < size_buff; position++)
        {
            symb = getchar ();
            if (isalpha (symb))
            {
                str = strctor (symb);
                // printf ("From %s we have %s with pointer: %p\n", __PRETTY_FUNCTION__, str, str);
                position += strlen (str);
                HashInsrt (hshmp, str);
                strdel (str);
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


        while (fgetc (file) != '\n') {;}
        for (symb = 1; feof (file) && symb != EOF;)
        {
            symb = fgetc (file);
            if (!isalpha (symb))
            {
                str = fstrctor (symb, file);
                position += strlen (str);
                HashInsrt (hshmp, str);
                strdel (str);
            }
        }
        fclose (file);
    }
    else
    {
        va_end (args);
        return INPUT_ERROR;
    }

    va_end (args);
    return NO_ERROR;
}

unsigned HashFind (const hashmap *hshmp, data_t data)
{
    assert (hshmp);
    unsigned key = (hshmp->hashcalc)(data) % (hshmp->capacity);
    unsigned conv, pos = 0;
    list_t *list = hshmp->array[key];

    if (!list)
        return 0;
    else
    {
        conv = 0;
        while (list)
        {
            if (istrcmp (list->data, data) == 0)
                conv++;
            list = list->next;
        }
    }

    return conv;
}

int ContestTask (hashmap *hshmp)
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
            printf ("%u ", HashFind (hshmp, str));
            position += strlen (str);
            strdel (str);
        }
    }
    printf ("\n");
    return NO_ERROR;
}

unsigned HashCalc (data_t data)
{
    unsigned hashkey = 5381;
    while (*data != '\0')
    {
        hashkey = ((hashkey << 5) + hashkey) + *data;
        data++;
    }
    return hashkey;
}

int HashInsrt (hashmap *hshmp, data_t insrt_data)
{
    //  initialization of new node of list  //
    list_t   *list    = (list_t *) calloc (1, sizeof (list_t));
    list->data        = (data_t) calloc (strlen (insrt_data) + 1, sizeof (char));
    list->data        = memmove (list->data, insrt_data, strlen (insrt_data));
    // printf ("From %s we have %s: pointer data %p; pointer list %p\n", __PRETTY_FUNCTION__, list->data, list->data, list);

    //  checking for resize  //
    if (hshmp->insertion > CRIT_KOEF * hshmp->capacity)
        HashResz (hshmp);

    assert (hshmp->array);

    unsigned hashkey = (*hshmp->hashcalc)(insrt_data) % (hshmp->capacity);

    if (!hshmp->array[hashkey])
        hshmp->array[hashkey] = list;
    else
    {
        list->next = hshmp->array[hashkey];
        hshmp->array[hashkey] = list;
    }

    hshmp->insertion++;
    return NO_ERROR;
}

int HashResz (hashmap *hshmp)
{
    assert (hshmp);

    //  initialization of sliders
    list_t *first, *second;

    //  initialization of new array
    unsigned new_capacity = ENCR_KOEF*hshmp->capacity;
    list_t **new_array = calloc (new_capacity, sizeof (list_t *));

    for (unsigned ip = 0; ip < hshmp->capacity; ip++)
    {
        if (hshmp->array[ip] == NULL)
            continue;
        else
        {
            first = hshmp->array[ip];
            while (first)
            {
                second = first;

                //  initialization of a node for list in new array  //
                list_t *nnode  = calloc (1, sizeof (list_t));
                nnode->data   = calloc (strlen(second->data) + 1, sizeof (char));
                nnode->data   = memmove (nnode->data, second->data, strlen(second->data));

                //  insertion of a node in new array  //
                unsigned nkey = (*hshmp->hashcalc) (nnode->data) % (new_capacity);
                if (!new_array[nkey])
                    new_array[nkey] = nnode;
                else
                {
                    nnode->next = new_array[nkey];
                    new_array[nkey] = nnode;
                }

                //  deleting data in old array  //
                free (second->data);
                free (second);

                first = first->next;
            }
        }
    }


    free (hshmp->array);
    hshmp->array    = new_array;
    hshmp->capacity = new_capacity;

    return NO_ERROR;
}

int HashDtor (hashmap *hshmp)
{
    assert (hshmp);
    list_t *first, *second;


    for (unsigned ip = 0; ip < hshmp->capacity; ip++)
    {
        first = hshmp->array[ip];
        if (!first)
            continue;
        else
        {
            while (first)
            {
                second = first;
                free (second->data);
                free (second);
                first = first->next;
            }
        }
    }

    free (hshmp->array);
    free (hshmp);

    return NO_ERROR;
}

void HashDump (hashmap *hshmp)
{
    int i = 0;
    list_t *list;

    printf ("_HASHMAP_\n");
    printf ("\tCAPACITY:   %u\n", hshmp->capacity);
    printf ("\tINSERTIONS: %u\n\n", hshmp->insertion);
    for (i = 0; i < hshmp->capacity; i++)
    {
        printf ("bucket[%d]:\n\t", i);
        list = hshmp->array[i];
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

int strdel (char * str)
{
    assert (str);
    free (str);
    return NO_ERROR;
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

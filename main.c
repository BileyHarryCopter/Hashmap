#include "hashmap.h"

int main (void)
{
    hashmap *hshmp;

    char *str1 = (char *) calloc (6, sizeof (char));
    str1[0] = 'p';
    str1[1] = 'i';
    str1[2] = 'z';
    str1[3] = 'd';
    str1[4] = 'a';

    hshmp = Hash_Ctor (SIZE_INIT, Hash_Calc);

    Hash_Fill (FSTDIO, hshmp);
    Hash_Insrt (hshmp, str1);
    //  Contest_Task (hshmp);

    Hash_Dump (hshmp);
    Hash_Dtor (hshmp);

    return 0;
}

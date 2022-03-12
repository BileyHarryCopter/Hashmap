#include "hashmap.h"

int main (void)
{
    hashmap *hshmp;

    hshmp = Hash_Ctor (SIZE_INIT, Hash_Calc);

    Hash_Fill (FSTDIO, hshmp);
    Contest_Task (hshmp);

    //  Hash_Dump (hshmp);
    
    Hash_Dtor (hshmp);
    return 0;
}

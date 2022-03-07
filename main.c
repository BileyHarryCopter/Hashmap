#include "hashmap.h"

int main (void)
{
    hashmap hshmp = {};

    Hash_Ctor (&hshmp, SIZE_INIT, Hash_Calc);

    Hash_Fill (&hshmp, "Data.txt");
    Contest_Task (hshmp, "Data.txt");

    //Hash_Dump (hshmp);
    Hash_Dtor (&hshmp);
    return 0;
}

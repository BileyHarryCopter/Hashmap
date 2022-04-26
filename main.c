#include "src/hashmap.h"

int main (int argv, char* argc[])
{
    hashmap *hshmp;
    hshmp = HashCtor (SIZE_INIT, HashCalc);
    HashFill (CONTEST, hshmp);
    // ContestTask (hshmp);

    // HashDump (hshmp);
    HashDtor (hshmp);
    return 0;
}

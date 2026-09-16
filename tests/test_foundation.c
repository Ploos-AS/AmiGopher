#include <stdio.h>
#include <string.h>

#include "amigopher/amigopher.h"

int main(void)
{
    if (strcmp(AMIGOPHER_NAME, "AmiGopher") != 0) {
        return 1;
    }
    if (AMIGOPHER_DEFAULT_PORT != 70) {
        return 1;
    }

    puts("AmiGopher M0 foundation: PASS");
    return 0;
}

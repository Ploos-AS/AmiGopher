#include <stdio.h>

#include "amigopher/amigopher.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("%s %s\n", AMIGOPHER_NAME, AMIGOPHER_VERSION);
    printf("Native Gopher client for AmigaOS 2.04+\n");
    printf("M0 foundation build - protocol/networking follows in later milestones.\n");

    return 0;
}

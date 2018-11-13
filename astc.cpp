#include <stdio.h>
#include <stdlib.h>
#include "astc.h"

void myExit(int exitCode) throw ()
{
    printf("ASTC encoder error: %d\n", exitCode);
}

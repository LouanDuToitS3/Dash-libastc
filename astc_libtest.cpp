#include <stdlib.h>
#include <stdio.h>
#include "astc.h"

void myExit(int) throw()
{
    printf("Exit local\n");
    exit(1);
}

int main(int argc, char const ** argv)
{
    astc_main(argc, const_cast<char**>(argv));

    printf("All done!\n");

    return 0;
}

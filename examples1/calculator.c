#include <stdio.h>
#include "cs50.h"

int main(void)
{
    long x = get_long("x:");
    long y = get_long("y:");

    double z = (double) x / (double) y;
    printf("%.20d\n", z);
}
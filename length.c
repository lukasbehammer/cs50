#include "cs50.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    string name = get_string("What's your name?:");
    /*
    int n = 0;
    while (name[n] != '\0')
    {
        n++;
    }
    */
    int n = strlen(name);

    printf("%i\n", n);
}
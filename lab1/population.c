#include "../cs50.h"
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start_size;
    do
    {
        start_size = get_int("Start size: ");
    }
    while (start_size < 9);
    // TODO: Prompt for end size
    int end_size;
    do
    {
        end_size = get_int("End size: ");
    }
    while (end_size < start_size);
    // TODO: Calculate number of years until we reach threshold
    int year_start = start_size;
    int year_end = 0;
    int years = 0;
    if (start_size != end_size)
    {
        while (year_end < end_size)
        {
            year_end = year_start + year_start/3 - year_start/4;
            year_start = year_end;
            years++;
        }
    }
    // TODO: Print number of years
    printf("Years: %i\n", years);
}

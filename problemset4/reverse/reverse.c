#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./reverse infile outfile\n");
        return 1;
    }

    // Open input file for reading
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // Read header
    WAVHEADER hd;
    fread(&hd, sizeof(WAVHEADER), 1, inptr);

    // Use check_format to ensure WAV format
    if (check_format(hd) == false)
    {
        printf("No WAV file given. \n");
        fclose(inptr);
        return 1;
    }

    // Open output file for writing
    FILE *outptr = fopen(argv[2], "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", argv[2]);
        return 1;
    }

    // Write header to file
    fwrite(&hd, sizeof(WAVHEADER), 1, outptr);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(hd);

    // Write reversed audio to file
    uint32_t buffer;
    int a = ftell(inptr);
    int n = 1;
    fseek(inptr, 0, SEEK_END);
    while (ftell(inptr) > a + block_size)
    {
        int ofst = n * block_size;
        fseek(inptr, -ofst, SEEK_END);
        fread(&buffer, block_size, 1, inptr);
        fwrite(&buffer, block_size, 1, outptr);
        n++;
    }

    fclose(inptr);
    fclose(outptr);
    return 0;
}

int check_format(WAVHEADER header)
{
    int frmt[4] = {'W', 'A', 'V', 'E'};
    for (int i = 0; i < 4; i++)
    {
        if (header.format[i] != frmt[i])
        {
            return false;
        }
    }
    return true;
}

int get_block_size(WAVHEADER header)
{
    int block_size;
    block_size = header.numChannels * (header.bitsPerSample / 8);
    return block_size;
}

#include "../../cs50.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    string text = get_string("Text: ");

    int letters = 0;
    int words = 0;
    int sentences = 0;

    for (int i = 0, n = strlen(text); i < n; i++) {
        char character = text[i];
        if (islower(text[i]) || isupper(text[i])) {
            letters++;
        } else {
            switch (text[i]) {
                case 32:
                    words++;
                    break;
                case 33:
                case 46:
                case 63:
                    sentences++;
                    break;
                default:
                    break;
            }
        }
    }
    words++;

    float L = (float) letters / words * 100;
    float S = (float) sentences / words * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;

    if (index > 16) {
        printf("Grade 16+\n");
    } else if (index < 0) {
        printf("Before Grade 1\n");
    } else {
        printf("Grade %i\n", (int) round(index));
    }
}
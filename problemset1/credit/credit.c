#include "../../cs50.h"
#include <stdio.h>

int main(void)
{
    // Get card number
    long card_number = get_long("Number: ");
    int digits = 0;
    long number = card_number;

    // Count digits
    while (number != 0)
    {
        number /= 10;
        digits++;
    }

    // Preallocate array
    int numberArray[digits];

    digits = 0;
    number = card_number;

    // Save digits to array
    while (number != 0)
    {
        numberArray[digits] = number % 10;
        number /= 10;
        digits++;
    }

    // Save each second digit to digitArray
    int c = 1;
    int i = 0;
    int digitArray[digits / 2];
    while (c < digits)
    {
        digitArray[i] = 2 * numberArray[c];
        c += 2;
        i++;
    }

    // Go through each element in digitArray
    int num1 = 0;
    for (int k = 0; k < digits / 2; k++)
    {
        int digits2 = 0;
        int number2 = digitArray[k];

        // Count digits
        while (number2 != 0)
        {
            number2 /= 10;
            digits2++;
        }

        int number2Array[digits2];

        digits2 = 0;
        number2 = digitArray[k];

        // Save digits to number2Array
        while (number2 != 0)
        {
            number2Array[digits2] = number2 % 10;
            number2 /= 10;
            digits2++;
        }

        // Sum digits in number2Array
        for (int l = 0; l < digits2; l++)
        {
            num1 += number2Array[l];
        }
    }

    // Calculate sum of other digits
    int j = 0;
    int num2 = 0;
    while (j < digits)
    {
        num2 += numberArray[j];
        j += 2;
    }
    // Check if last digit of full sum is 0
    int num3 = num1 + num2;
    int valid = num3 % 10;

    // Conditions for each distributor
    if (valid == 0 && digits == 15 && numberArray[14] == 3 && (numberArray[13] == 4 || numberArray[13] == 7))
    {
        printf("AMEX\n");
    }
    else if (valid == 0 && digits == 16 && numberArray[15] == 5 && (numberArray[14] >= 1 && numberArray[14] <= 5))
    {
        printf("MASTERCARD\n");
    }
    else if (valid == 0 && ((digits == 16 && numberArray[15] == 4) || (digits == 13 && numberArray[12] == 4)))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
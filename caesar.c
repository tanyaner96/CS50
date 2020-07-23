#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include<stdlib.h>
#include <ctype.h>
#include <string.h>

int main (int argc, string argv[])
{
    //check if argc == 2
    //prompt if not 2 and say FAIL
    //convert to int, check if negative
    //check for non numbers

    //prompt user for string
    //convert string
    //return the ciphered text

    string input = argv[1];
    int length = strlen(input);

    //convert string to number
    int cipher;
    cipher = atoi(input);

    if (argc == 2)
    {
        //check for positive nums
        if (cipher == 0 ||cipher < 0)
        {
            printf("Usage: ./caesar key\n");
            exit(0);
        }
        else
        {
            // check for non numbers (doesn't work when is single digit and letter)
            for(int i=0; i<length; i++)
            {
                if isdigit(input[i])
                {

                }
                else
                {
                    printf("Usage: ./caesar key\n");
                    exit(0);
                }
            }
        }

    }
    else
    {
        printf("Usage: ./caesar key\n");
    }

    // prompt for text (Prompts even if no key oops)
    string text = get_string("plaintext: ");



    // convert plaintext to ciphertext ci = (pi + k) % 26
    int textLength = strlen(text);

    printf("ciphertext: ");

    for(int i = 0; i<textLength; i++)
    {
        if (text[i] < 91 && text[i] > 64) //If letter is uppercase
        {
            // printf("It's an uppercase\n");

            int ascii = text[i];
            // printf("ASCII Decimal is: %i\n", ascii);

            int position = ascii - 65;
            // printf("Position: %i\n", position);

            int ci = (position + cipher)%26;
            // printf("ci: %i\n", ci);

            int NewPosition = ci + 65;
            // printf("New position: %i\n", NewPosition);

            printf("%c", NewPosition);

        }
        else if(text[i] < 123 && text[i] > 96) //If letter is lowercase
        {
            // printf("It's an lowercase\n");

            int ascii = text[i];
            // printf("ASCII Decimal is: %i\n", ascii);

            int position = ascii - 97;
            // printf("Position: %i\n", position);

            int ci = (position + cipher)%26;
            // printf("ci: %i\n", ci);

            int NewPosition = ci + 97;
            // printf("New position: %i\n", NewPosition);

            printf("%c", NewPosition);
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
}
#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>



int main(void)
{
    //get user input
    string text = get_string("Text: ");

    //count length of text w/ spaces
    int length = strlen(text);
    // printf("Total length: %i letters\n", length);

    //check every character if is space
    int space = 0;
    for (int i=0; i<length; i++)
    {
        if(isspace(text[i]))
        {
            space = space + 1;
        }
    }

    //Number of letters w/o space (still includes punctuation)
    int letterNum = length - space;
    // printf("Without spaces: %i letters\n", letterNum);

    //check for punctuation
    int punct = 0;
    for (int i=0; i<length; i++)
    {
        if(ispunct(text[i]))
        {
            punct = punct + 1;
        }
    }
    //number of letters
    int num = letterNum - punct;
    // printf("%i punctuation(s)\n", punct);
    // printf("%i letter(s)\n", num);

    //count words --> number of spaces + 1
    int words = space + 1;
    // printf("%i word(s)\n", words);

    //count number of sentences
    int sentence = 0;
    for (int i=0; i<length; i++)
    {
        if (text[i] == '.'|| text[i] == '?' || text[i] == '!')
        {
            sentence = sentence + 1;
        }
    }
    // printf("%i sentence(s)\n", sentence);

    // index = 0.0588 * L - 0.296 * S - 15.8
    // L: average number of letters per words in the text X 100
    // S: average number of sentences per words in the text X 100

    float L =  ((float)num/ words) *100;
    // printf("L = %f\n", L);

    float S =  ((float)sentence/words) *100;
    // printf("S = %f\n", S);

    float index = 0.0588 * L - 0.296 * S - 15.8;

    if (index>15)
    {
        printf("Grade 16+\n");
    }
    else if (index<1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %.0f \n", round(index));
    }

}
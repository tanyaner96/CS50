#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height = get_int("Height:");

    while (height >8 || height <1)
    {
        printf("Again!\n");
        height=get_int("Height:");
    }


    for(int row = 1; row < height + 1; row = row + 1)
    {
        //numSpaces - number of spaces before hex 
        int numSpaces = height - row;
        for (int count = 0; count < numSpaces; count = count + 1)
        {
            printf(" ");
        }
        
        //left side of pyramid
        int numHex = height - numSpaces;
        for(int count = 0;count < numHex; count = count + 1)
        {
            printf("#");
        }

        printf("  ");

        //right side of pyramid
        numHex = height - numSpaces;
        for(int count = 0;count < numHex; count = count + 1)
        {
            printf("#");
        }

        printf("\n");

    }
}




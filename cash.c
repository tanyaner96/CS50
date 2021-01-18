#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change = get_float("Change owed: ");

    while(change < 0)
    {
        change = get_float("Change owed: ");
    }

    //convert to cents
    int cents = round(change * 100);
    //printf("cents: %i\n", cents);

    //First: calculate number of 25cent coins needed.
    int numTF = floor(cents/25);
    int amtTF= numTF * 25;
    int first = cents - amtTF;
    //printf("amtTF: %i\n", amtTF);
    //printf("first: %i\n", first);

    //Second: calculate number of 10cent coins needed.
    int numT = floor(first/10);
    int amtT = numT*10;
    int second = first - amtT;
    //printf("amtT: %i\n", amtT);
    //printf("second: %i\n", second);

    //Third: calculate number of 5cent coins needed.
    int numF = floor(second/5);
    int amtF = numF*5;
    int third = second - amtF;
    //printf("amtF: %i\n", amtF);
    //printf("third: %i\n", third);

    //Fourth: calculate number of 1cent coins needed.
    int numO = floor(third/1);
    int amtO = numO*1;
    int final = third - amtF;
    

    //Tally up total number of coins
    int Total = numTF + numT + numF + numO;
    
    printf("%i\n", Total);
}
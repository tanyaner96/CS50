#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("May I inquire as to how I should address you, brave adventurer?\n");
    printf("Well hello there, %s! Welcome to CS50!\n", name);
}

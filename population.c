#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int population_size = get_int("Population size: ");

    while (population_size < 9)
    {
        population_size = get_int("Population size: ");
    }

    // TODO: Prompt for end size
    int end_size = get_int("End size: ");

    if (end_size < population_size)
    {
        end_size = get_int("End size: ");
    }
    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    while (population_size < end_size)
    {
        population_size = population_size + population_size/3 - population_size/4;
        years = years + 1;
    }

    // TODO: Print number of years
    printf("Years: %i \n", years);
}
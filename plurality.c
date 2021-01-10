#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    //printf("This is the vote function\n");
    for (int i = 0; i < candidate_count; i++)
    {
        //printf("%s \n", candidates[i].name);
        if (strcmp(name, candidates[i].name) == 0)
        {
            //printf("The if worked\n");
            candidates[i].votes = candidates[i].votes + 1;
            return true;
        }
    }

    // TODO
    //If name matches one of names of candidates in the election, update candidate’s vote total to account for new vote.
    //Vote function should return true to indicate a successful ballot
    //If name does not match any candidates, no vote totals should change
    //Vote function should return false to indicate invalid ballot

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    //The function should print out the name of the candidate who received the most votes in the election, and then print a newline.
    //If tie, output the names of each of the winning candidates, each on a separate line.

    //Display list of votes
    //for (int i = 0; i < candidate_count; i++)
    {
        //printf("%s ", candidates[i].name);
       // printf("%i \n", candidates[i].votes);
    }

    int winner;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes>candidates[i-1].votes)
        {
           winner = i;
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == candidates[winner].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }


    return;
}


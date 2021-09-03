//This is a C-program that count votes in a plurality voting structure

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
// Number og voters
int voter_count;


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

    voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name_voted = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name_voted))
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
    for (int a = 0; a < candidate_count; a++)
    {
        if (strcmp(candidates[a].name, name) == 0)
        {
            candidates[a].votes++;
            return true;
        }
    }
    return false;
}
// Print the winner (or winners) of the election
void print_winner(void)
{
    int flest;//int to place the candidate with the most votes inn
    int antall = 0;//place tol hold the "current" highest votes.
    for (int y = 0; y < candidate_count; y++)
    {
        for (int i = 0; i < MAX; i++)
        {
            if (candidates[i].votes > antall)
            {
                antall = candidates[i].votes;
                flest = i;
            }
        }
    }
    printf("%s\n", candidates[flest].name);//print the winner
    for (int z = 0; z < candidate_count; z++)//check over all the names to see if there are several winners
    {
        if (candidates[z].votes == candidates[flest].votes
            && strcmp(candidates[z].name, candidates[flest].name) != 0)//if they have the same name, ignore them.
        {
            printf("%s\n", candidates[z].name);
        }
    }
}
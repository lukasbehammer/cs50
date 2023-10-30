#include "../../cs50.h"
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];
bool lock = true;

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner();
void calc_rank(int candidate_count);
int search_winner(int row);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
            preferences[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Alice Bob Charlie

    // Charlie Alice Bob
    // ranks = {2, 0, 1}
    // --> preferences =    {{*, 1, *}, {*, *, *}, {1, 1, *}}
    // Alice Charlie Bob
    // ranks = {0, 2, 1}
    // --> preferences =    {{*, 2, 1}, {*, *, *}, {1, 2, *}}
    // Alice Bob Charlie
    // ranks = {0, 1, 2}
    // --> preferences =    {{*, 3, 2}, {*, *, 1}, {1, 2, *}}
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // preferences =    {{*, 3, 2}, {0, *, 1}, {1, 2, *}}
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    // --> pairs = {{0, 1}, {0, 2}, {2, 1}}
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // pairs = {{0, 1}, {0, 2}, {2, 1}}
    // preferences = {{*, 3, 2}, {0, *, 1}, {1, 2, *}}

    pair temp;
    for (int i = 0; i < pair_count - 1; i++)
    {
        int highest_n = 0;
        for (int j = i; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > highest_n)
            {
                temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
                highest_n = preferences[pairs[j].winner][pairs[j].loser];
            }
        }
    }
    // --> pairs = {{0, 1}, {0, 2}, {2, 1}}
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // pairs = {0, 1}, {0, 2}, {2, 1}
    // winner = {1, 0, 0}
    // loser = {0, 1, 0}
    // winner = {2, 0, 0}
    // loser = {0, 1, 1}
    // winner = {2, 0, 1}
    // loser = {0, 2, 1}

    // pairs = {0, 1}, {1, 2},      {2, 0}
    // winner = {1, 1, 0}
    // loser = {0, 1, 1}

    // pairs = {0, 1}, {2, 3}, {1, 2},      {3, 0}
    // winner = {1, 1, 1, 0}
    // loser = {0, 1, 1, 1}

    // pairs = {0, 1}, {1, 2}, {2, 3}, {0, 3},      {3, 1}
    // winner = {2, 1, 1, 0}
    // loser = {0, 1, 1, 2}

    // pairs = {0, 1}, {1, 2}, {2, 3}, {0, 3}, {3, 1}
    // winner = {2, 1, 1, 1}
    // loser = {0, 2, 1, 2}

    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;

        calc_rank(candidate_count);

        if (lock == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
        lock = true;
    }
    return;
    // --> times_winner = {2, 0, 1}
    // --> times_loser = {0, 2, 1}
}

// check for cycles
void calc_rank(int candidate_num)
{
    if (candidate_num == 0)
    {
        return;
    }

    bool rows[candidate_num];
    int rank = 0;

    for (int i = 0; i < candidate_num; i++)
    {
        rows[i] = false;
    }

    calc_rank(candidate_num - 1);

    for (int i = 0; i < candidate_num; i++)
    {
        for (int j = 0; j < candidate_num; j++)
        {
            if (locked[i][j] == true)
            {
                rows[i] = true;
            }
        }
    }

    for (int i = 0; i < candidate_num; i++)
    {
        if (rows[i] == true)
        {
            rank++;
        }
    }

    if (rank == candidate_num)
    {
        lock = false;
    }
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                printf("%s\n", candidates[search_winner(i)]);
                return;
            }
        }
    }
}

// Search for the beginning of the graph
int search_winner(int row)
{
    int winner = row;
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][row] == true)
        {
            winner = search_winner(i);
        }
    }
    return winner;
}

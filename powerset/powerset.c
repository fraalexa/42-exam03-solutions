#include <stdio.h>
#include <stdlib.h>

void backtrack(int *set, int n_elements, int target, int *subset, int subset_size, int index, int current_sum)
{
    if (index == n_elements)  // reached end
    {
        if (current_sum == target)
        {
            for (int i = 0; i < subset_size; i++)
            {
                if (i) printf(" ");
                printf("%d", subset[i]);
            }
            printf("\n");
        }
        return;
    }

    // Option 1: include current element
    subset[subset_size] = set[index];
    backtrack(set, n_elements, target, subset, subset_size+1, index+1, current_sum + set[index]);

    // Option 2: skip current element
    backtrack(set, n_elements, target, subset, subset_size, index+1, current_sum);
}

int main(int argc, char **argv)
{
    if (argc < 3) return 1;

    int target = atoi(argv[1]);
    int n = argc - 2;
    int *set = malloc(sizeof(int) * n);
    int *subset = malloc(sizeof(int) * n);
    if (!set || !subset) return 1;

    for (int i = 0; i < n; i++)
        set[i] = atoi(argv[i+2]);

    backtrack(set, n, target, subset, 0, 0, 0);

    free(set);
    free(subset);
    return 0;
}

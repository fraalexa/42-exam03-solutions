#include <unistd.h>


static void putstr(char *s)
{
    while (*s)
        write(1, s++, 1);
    write(1, "\n", 1);
}

/*
** First pass: compute how many '(' and ')' must be removed
*/
static void count_removals(char *s, int *left, int *right)
{
    int i = 0;
    int open = 0;

    while (s[i])
    {
        if (s[i] == '(')
            open++;
        else if (s[i] == ')')
        {
            if (open > 0)
                open--;
            else
                (*right)++;
        }
        i++;
    }
    *left = open;
}

/*
** Backtracking
*/
static void solve(char *s, int index, int open,
                  int left_rem, int right_rem)
{
    if (!s[index])
    {
        if (open == 0 && left_rem == 0 && right_rem == 0)
            putstr(s);
        return;
    }

    if (s[index] == '(')
    {
        // Option 1: remove it
        if (left_rem > 0)
        {
            s[index] = ' ';
            solve(s, index + 1, open, left_rem - 1, right_rem);
            s[index] = '(';
        }

        // Option 2: keep it
        solve(s, index + 1, open + 1, left_rem, right_rem);
    }
    else if (s[index] == ')')
    {
        // Option 1: remove it
        if (right_rem > 0)
        {
            s[index] = ' ';
            solve(s, index + 1, open, left_rem, right_rem - 1);
            s[index] = ')';
        }

        // Option 2: keep it (only if valid)
        if (open > 0)
            solve(s, index + 1, open - 1, left_rem, right_rem);
    }
}

int main(int ac, char **av)
{
    int left = 0;
    int right = 0;

    if (ac != 2)
        return (1);

    count_removals(av[1], &left, &right);
    solve(av[1], 0, 0, left, right);
    return (0);
}

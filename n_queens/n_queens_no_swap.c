#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void ft_swap(int *a, int *b)
{
 	int tmp;
	
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	under_attack(int *pos, int x)
{
	int i = 0;
	int d;

	
	while (i < x)
	{
		d = x - i;
		if (pos[i] == pos[x])
			return (0);
		if (pos[i] == pos[x] - d)
			return (0);
		if (pos[i] == pos[x] + d)
			return (0);
		i++;
	}
	return (1);
}

void	recursion_alg(int	*pos, int n, int x)
{
	if (x == n)
	{
		for(int i = 0; i < n; i++)
		{
			printf("%d", pos[i]);
			if (i < n - 1)
				printf(" ");
		}
		printf("\n");
	}

	for(int i = 0; i < n; i++)
	{
		pos[x] = i;
		if(under_attack(pos, x))
			recursion_alg(pos, n , x + 1);
	}
	return ;
}

int main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	int n = atoi(av[1]);
	if (n == 1)
	{
		printf("0\n");
		return 0;
	}
	if (n < 4)
		return 0;
	int pos[n];
	recursion_alg(pos, n, 0);
}
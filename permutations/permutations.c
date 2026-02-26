#include <unistd.h>

int f_strlen(char *s)
{
	int i = 0;
	while(*s)
	{
		i++;
		s++;
	}
	return i;
}
void	ft_swap(char *s, char *s1)
{
	char c = *s;
	*s = *s1;
	*s1 = c;
}

void	bubblesort(char *s, int n)
{
	int flag = 1;

	while(flag)
	{
		flag = 0;
		for(int i = 0; i < n - 1; i++)
		{
			if (s[i] > s[i + 1])
			{
				ft_swap(&s[i], &s[i + 1]);
				flag = 1;
			}
		}
		n--;
	}
}

void 	back_track(char *s, int len, int *used, char *out, int depth)
{
	if (depth == len)
	{
		write(1, out, len);	
		write(1, "\n", 1);
		return ;
	}
	for (int j = 0; j < len; j++)
	{
		if (used[j])
			continue ;
		used[j] = 1;
		out[depth] = s[j];
		back_track(s, len, used, out, depth + 1);
		used[j] = 0;
	}
	return ;
}

int main(int ac,  char **av)
{
	if (ac != 2 || !av[1][0])
		return (1);
	int len = f_strlen(av[1]);
	int used[len];
	char out[len];
	for (int i = 0; i < len; i++)
		used[i] = 0;
	bubblesort(av[1],len);
	back_track(av[1], len, used, out, 0);
	return (0);

}
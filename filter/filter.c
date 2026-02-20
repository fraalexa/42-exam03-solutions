#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1024

int	main(int argc, char **argv)
{
	char	*pattern;
	int	pat_len;
	char	buf[BUF_SIZE];
	char	*store = NULL;
	int	store_len = 0;
	int	r;

	if (argc != 2 || !argv[1][0])
		return (1);
	pattern = argv[1];
	pat_len = strlen(pattern);

	while ((r = read(0, buf, BUF_SIZE)) > 0)
	{
		char *tmp = realloc(store, store_len + r);
		if (!tmp)
			return (free(store), 1);
		store = tmp;
		memcpy(store + store_len, buf, r);
		store_len += r;

		char *match;
		while ((match = memmem(store, store_len, pattern, pat_len)))
		{
			int prefix = match - store;
			write(1, store, prefix);
			for (int i = 0; i < pat_len; i++)
				write(1, "*", 1);
			memmove(store, match + pat_len,
				store_len - prefix - pat_len);
			store_len -= prefix + pat_len;
		}
	}
	if (r < 0)
		return (free(store), 1);
	if (store_len > 0)
		if (write(1, store, store_len) < 0)
			return (free(store), 1);
	free(store);
	return (0);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	size_t	len;
	size_t	i;
	char	buffer[100];

	fgets(buffer, 100, stdin);
	len = strlen(buffer);
	for (i = 0; i < len; ++i) {
		if (buffer[i] > '@' && buffer[i] <= 'Z')
			buffer[i] ^= ' ';
	}
	printf(buffer);
	exit(0);
}
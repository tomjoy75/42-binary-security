#include <stdio.h>
#include <string.h>

int	main(int argc, char **argv)
{
	(void)argc;
	unsigned int	hash;
	const char	*buffer = argv[1];
	size_t	len = strlen(buffer);

	hash = (buffer[3] ^ 4919) + 6221293;
	for (size_t i = 0; i < len; ++i) {
		if (buffer[i] < 32)
			return 1;
		hash += (hash ^ (unsigned int)buffer[i]) % 1337;
	}

	printf("res = %u\n", hash);
	return 0;
}
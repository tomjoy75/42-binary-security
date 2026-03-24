#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	main(int argc, char **argv)
{
	(void)argc;

	int	ret;
	int	value;
	char	buffer[40];

	value = atoi(argv[1]);
	if (value < 10) {
		memcpy(buffer, argv[2], value * 4);
		if (value == 0x574f4c46)
			execl("/bin/sh", "sh", NULL);
		ret = 0;
	} else {
		ret = 1;
	}
	return ret;
}
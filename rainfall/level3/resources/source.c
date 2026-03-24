#include <stdio.h>
#include <stdlib.h>

int m;

void	v(void)
{
	char	buffer[512];

	fgets(buffer, 512, stdin);
	printf(buffer);
	if (m == 0x40) {
		fwrite("Wait what ?!\n", sizeof(char), 12, stdout);
		system("/bin/sh");
	}
}

int	main(void)
{
	v();
	return 0;
}
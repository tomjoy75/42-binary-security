#include <stdio.h>
#include <stdlib.h>

void	p(void)
{
	unsigned int	ret;
	char	buffer[76];
	
	fflush(stdout);
	gets(buffer);
	ret = __builtin_return_address(0);
	if ((ret & 0xb0000000) == 0xb0000000) {
		printf("(%p)\n", ret);
		exit(1);
	}

	puts(buffer);
	strdup(buffer);
}

int	main(void)
{
	p();
	return 0;
}
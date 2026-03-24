#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	n(void)
{
	system("/bin/cat /home/user/leve7/.pass");
}

void	m(void)
{
	puts("Nope");
}

int	main(int argc, char **argv)
{
	char	*dest = malloc(64);
	void	(**func_ptr)() = malloc(4);

	*func_ptr = m;
	strcpy(dest, argv[1]);
	(*func_ptr)();

	return 0;
}
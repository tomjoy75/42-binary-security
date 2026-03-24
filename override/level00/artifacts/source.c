#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int	password[4];

	puts("***********************************");
	puts("* \t     -Level00 -\t\t  *");
	puts("***********************************");

	printf("Password:");
	scanf("%d", password);

	if (password[0] != 5276) {
		puts("\nInvalid Password!");
	}
	else {
		puts("\nAuthenticated!");
		system("/bin/sh");
	}

	return password[0] != 5276;
}
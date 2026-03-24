#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>

int	auth(char *buffer, unsigned int serial)
{
	size_t	len;
	unsigned int	hash;

	buffer[strcspn(buffer, "\n")] = '\0';
	len = strnlen(buffer, " ");
	if (len < 6)
		return 1;
	if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1) {
		puts("\x1b[32m.---------------------------.");
		puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
		puts("\x1b[32m\'---------------------------\'");
		return 1;
	}

	hash = (buffer[3] ^ 4919) + 6221293;
	for (size_t i = 0; i < len; ++i) {
		if (buffer[i] < 32)
			return 1;
		hash += (hash ^ (unsigned int)buffer[i]) % 1337;
	}
	return (hash == serial) ? 0 : 1;
}

int	main(void)
{
	unsigned int	serial;
	char	buffer[32];

	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");
	printf("-> Enter Login: ");
	fgets(buffer,32,stdin);
	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");
	printf("-> Enter Serial: ");
	scanf("%u", serial);

	if (auth(buffer, serial))
		return 1;

	puts("Authenticated!");
	system("/bin/sh");
	return 0;
}
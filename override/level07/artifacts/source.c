#include <stdio.h>
#include <string.h>

void	clear_stdin(void)
{
	int	c;

	do
		c = getchar();
	while (c != '\n' && c != EOF);
}

int	get_unum(void)
{
	unsigned int	num;
	fflush(stdout);
	scanf("%u", &num);
	clear_stdin();
	return num;
}

int	store_number(int *data)
{
	printf("Number: ");
	int number = get_unum();
	printf("Index: ");
	int index = get_unum();

	if ((index % 3 == 0) || (number >> 24 == 0xb7)) {
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");
		return 1;
	}

	data[index] = number;
	return 0;
}

int	read_number(int *data)
{
	printf(" Index: ");
	int index = get_unum();
	printf("Number at data[%u] is %u\n", index, *(unsigned int *)(index * 4 + data));
	return 0;
}

int	main(int argc, char **argv, char **envp)
{
	int	result;
	unsigned int	data[100];
	char	command[20];

	memset(data, 0, sizeof(data));
	for (char **ptr = argv; *ptr; ptr++)
		memset(*ptr, 0, strlen(*ptr));
	for (char **ptr = envp; *ptr; ptr++)
		memset(*ptr, 0, strlen(*ptr));

	puts(
    "----------------------------------------------------\n"
    "  Welcome to wil's crappy number storage service!   \n"
    "----------------------------------------------------\n"
    " Commands:                                          \n"
    "    store - store a number into the data storage    \n"
    "    read  - read a number from the data storage     \n"
    "    quit  - exit the program                        \n"
    "----------------------------------------------------\n"
    "   wil has reserved some storage :>                 \n"
    "----------------------------------------------------\n");

	while (1) {
		printf("Input command: ");
		result = 1;
		fgets(command, 20, stdin);
		command[strlen(command) - 1] = '\0';
		if (!memcmp(command, "store", 5))
			result = store_number((int *)data);
		else if (!memcmp(command, "read", 4))
			result = read_number((int *)data);
		else if (!memcmp(command, "quit", 4))
			return 0;

		if (result)
			printf("Failed to do %s command\n", command);
		else
			printf("Completed %s command successfully\n", command);

		memset(command, 0, sizeof(command));
	}
	return 0;
}
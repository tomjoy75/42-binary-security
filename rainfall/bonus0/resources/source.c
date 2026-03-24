#include <unistd.h>
#include <stdio.h>
#include <string.h>

void	p(char *input, char *delim)
{
	char	*buffer_newline;
	char	buffer[4104];

	puts(delim);
	read(stdin, buffer, 4096);
	buffer_newline = strchr(buffer, '\n');
	*buffer_newline = '\0';
	strncpy(input, buffer, 20);
}

void	pp(char *dest)
{
	size_t	len;
	char	first_input[20];
	char	second_input[20];

	p(first_input, " - ");
	p(second_input, " - ");
	strcpy(dest, first_input);
	len = strlen(dest);
	dest[len] = ' ';
	dest[len + 1] = '\0';
	strcat(dest, second_input);
}

int	main(void)
{
	char	dest[42];

	pp(dest);
	puts(dest);
	return 0;
}
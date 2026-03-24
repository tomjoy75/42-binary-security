#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(int argc, char **argv)
{
	char	flag_buffer[65];
	char	copy_flag_buffer[66];
	FILE	*stream = fopen("/home/user/end/.pass", "r");	

	memset(flag_buffer, 0, 65);
	if (!stream || argc != 2)
		return 255;

	fread(flag_buffer, 1, 66, stream);
	int	buffer_delim = atoi(argv[1]);
	flag_buffer[buffer_delim] = '\0';

	fread(copy_flag_buffer, 1, 65, stream);
	fclose(stream);

	if (!strcmp(flag_buffer, argv[1]))
		execl("/bin/sh", "sh", NULL);

	puts(copy_flag_buffer);
	return 0;
}
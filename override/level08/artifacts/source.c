#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

void	log_wrapper(FILE *stream, const char *message, const char *file)
{
	size_t	buffer_size;
	char	buffer[264];

	strcpy(buffer, message);
	buffer_size = strlen(buffer);
	snprintf(&buffer[buffer_size], 254 - buffer_size, file);
	buffer[strcspn(buffer, "\n")] = '\0';
	fprintf(stream, "LOG: %s\n", buffer);
}

int	main(int argc, char **argv)
{
	FILE	*log;
	FILE	*stream;
	int	fd;
	char	c;
	char	dest[104];

	if (argc != 2)
		printf("Usage: %s filename\n", *argv);

	log = fopen("./backups/.log", "w");
	if (!log) {
		printf("ERROR: Failed to open %s\n", "./backups/.log");
		exit(1);		
	}

	log_wrapper(log, "Starting back up: ", argv[1]);
	stream = fopen(argv[1], "r");
	if (!stream) {
		printf("ERROR: Failed to open %s\n", argv[1]);
		exit(1);
	}

	strncpy(dest, "./backups/", 11);
	strncat(dest, argv[1], 99 - strlen(dest));
	
	fd = open(dest, O_WRONLY | O_CREAT | O_EXCL, 0660);
	if (fd < 0) {
		printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
		exit(1);
	}

	while (1) {
		c = fgetc(stream);
		if (c == -1)
			break;
		write(fd, &c, 1); 
	}

	log_wrapper(log, "Finished back up", argv[1]);
	fclose(stream);
	close(fd);
	return 0;
}
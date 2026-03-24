#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	size_t	ret;
	char	password[112];
	char	flag_buffer[48];
	char	user_name[100];
	FILE	*stream;

	memset(user_name, 0, sizeof(user_name));
	memset(flag_buffer, 0, sizeof(flag_buffer));
	memset(password, 0, sizeof(password));
	stream = fopen("/home/users/level03/.pass", "r");
	if (!stream) {
		fwrite("ERROR: failed to open password file\n", sizeof(char), 36, stderr);
		exit(1);
	}

	ret = fread(flag_buffer, sizeof(char), 41, stream);
	if (ret != 41) {
		fwrite("ERROR: failed to read password file\n", sizeof(char), 36, stderr);
		exit(1);
	}

	ret = strcspn(flag_buffer, "\n");
	flag_buffer[ret] = '\0';
	fclose(stream);

	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\\**************************************/");
	
	printf("--[ Username: ");
	fgets(user_name, 100, stdin);
	ret = strcspn(user_name, "\n");
	user_name[ret] = '\0';

	printf("--[ Password: ");
	fgets(password, 100, stdin);
	ret = strcspn(password, "\n");
	password[ret] = '\0';
	puts("*****************************************");

	if (strncmp(flag_buffer, password, 41)) {
		printf(user_name);
		puts(" does not have access!");
		exit(1);
	}

	printf("Greeting, %s!\n", user_name);
	system("/bin/sh");
	return 0;
}
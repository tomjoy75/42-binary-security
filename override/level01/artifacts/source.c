#include <stdio.h>
#include <string.h>

char	user_name[100];

int	verif_user_name(void)
{
	puts("verifying username.....\n");
	memcmp(user_name, "dat_wil", 7) != 0;
}

int	verif_user_pass(const char *password)
{
	return memcmp(password, "admin", 5) != 0;
}

int	main(void)
{
	int	ret;
	char	user_password[64];

	memset(user_password, 0, sizeof(user_password));
	puts("********* ADMIN LOGIN PROMPT *********");
	printf("Enter Username: ");

	fgets(user_name, 256, stdin);
	ret = verif_user_name();
	if (ret) {
		puts("nope, incorrect username...\n");
	}
	else {
		puts("Enter Password: ");
		fgets(user_password, 100, stdin);
		ret = verif_user_pass(user_password);
		puts("nope, incorrect password....\n");
	}

	return 1;
}
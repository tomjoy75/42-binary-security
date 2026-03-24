#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	language;

int	greetuser(char *src)
{
	char	dest[64];

	switch (language) {
	case 1:
		strcpy(dest, "Hyvää päivää ");
		break;
	case 2:
		strcpy(dest, "Goedemiddag! ");
		break;
	case 0:
		strcpy(dest, "Hello ");
		break;
	}

	strcat(dest, src);
	return puts(dest);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		return 1;

	char	user_input[72];
	char	*lang;
	
	strncpy(user_input, argv[1], 40);
	strncpy(&user_input[40], argv[2], 32);

	lang = getenv("LANG");
	if (lang) {
		if (!memcmp(lang, "fi", 2))
			language = 1;
		if (!memcmp(lang, "nl", 2))
			language = 2;
	}

	return greetuser(user_input);
}
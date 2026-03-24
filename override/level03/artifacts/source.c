#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int	decrypt(int key)
{
	char	hash[17] = "Q}|u`sfg~sf{}|a3";

	for (int i = 0; hash[i]; i++)
		hash[i] ^= key;

	if (!strcmp(hash, "Congratulations!"))
		return system("/bin/sh");

	puts("\nInvalid Password");
	return 0;
}

int	test(int user_input, int secret)
{
	int	key = secret - user_input;

	switch (key) {
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
		return decrypt(key);
	default:
		return decrypt(rand());
	}

	return 0;
}

int	main(void)
{
	int	input;
	time_t	t = time(NULL);
	
	srand(t);
	puts("***********************************");
	puts("*\t\tlevel03\t\t**");
	puts("***********************************");
	printf("Password:");

	scanf("%d", &input);
	test(input, 322424845);

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	int key;
	char	*win_condition = "Congratulations!";

	for (key = 1; key <= 21; key++) {
		char	hash[] = "Q}|u`sfg~sf{}|a3";
		size_t	hash_len = strlen(hash);
		
		for (int i = 0; i < hash_len; ++i)
			hash[i] ^= key;
	
		if (!strcmp(hash, win_condition))
			break;
	}

	printf("Password is %d\n", 322424845 - key);
	return 0;
}
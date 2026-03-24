#include <stdlib.h>
#include <limits.h>

int	main(void)
{
	int	i;
	size_t	res = 0;
	for (i = INT_MIN; i < 0; i++) {
		res = i * 4;
		if (res == 44)
			break;
	}
	printf("needed offset: %zu\tint: %d\n", res, i);
	return 0;
}
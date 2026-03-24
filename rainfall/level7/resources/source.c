#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char	c[68];

typedef struct {
	int	x;
	char	*buffer;
} foo;

void	m(void)
{
	time_t	t = time(NULL);
	printf("%s - %d\n", c, t);
}

int	main(int argc, char **argv)
{
	foo	*a, *b;
	void	*buffer;
	FILE	*stream;
	
	a = (foo *)malloc(8);
	a->x = 1;
	buffer = malloc(8);
	a->buffer = buffer;

	b = (foo *)malloc(8);
	b->x = 2;
	buffer = malloc(8);
	b->buffer = buffer;

	strcpy(a->buffer, argv[1]);
	strcpy(b->buffer, argv[2]);
	stream = fopen("/home/user/level8/.pass", "r");
	fgets(c, 68, stream);
	puts("~~");

	return 0;
}
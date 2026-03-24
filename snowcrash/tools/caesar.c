#include <stdio.h>
#include <string.h>

int	main(void){
	char	str[] = "cdiiddwpgswtgt";
	unsigned char	c;
//	int		len = strlen(str);

//	printf("length : %d\n", len);
	for (int i = 0; i < 26; i++){
	   printf("offset %d : ", i);
	   for (int j = 0; j < strlen(str) ; j++){
		  c = str[j] + i;
		  if (c > 'z')
			  c -= 26;
		  printf("%c", c);
		}
	   printf("\n");
	}
}

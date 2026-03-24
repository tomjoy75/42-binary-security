# Level 09

```bash
level09@SnowCrash:~$ ls -l 
total 12
-rwsr-sr-x 1 flag09 level09 7640 Mar  5  2016 level09
----r--r-- 1 flag09 level09   26 Mar  5  2016 token
```

En lisant le resultat de la commande 'strings level09' On s'appercoit que l'executable contient des protections contre les injection de lib dynamique
En utilisant le site dogbolt, pour decompiler le binaire on peut remarquer ce bout de code

```c
	if (argc != 2)
		return fwrite("You need to provied only one arg.\n", 1u, 0x22u, stderr);
	while (++v4 < strlen(argv[1]))
		putchar(v4 + argv[1][v4]);
```

Il semblerait que le programme accepte un argument puis affiche chaque caractere incrementer par son index

```bash
level09@SnowCrash:~$ ./level09 00000
01234
```

En utilisant sur le contenu du fichier 'token' on obtient

```bash
level09@SnowCrash:~$ ./level09 $(cat token)
f5mpq;v�E��{�{��TS�W�����
```

Ecrivons un petit programme C qui va nous permettre de decoder la chaine contenue dans le fichier 'token' en decrementant le caractere par son index

```c
#include <stdio.h>

int	main(int argc, char **argv)
{
	(void)argc;
	for (int i = 0; argv[1][i] != '\0'; i++)
		printf("%c", argv[1][i] - i);
	printf("\n");
	return 0;
}
```

Une fois le fichier 'token' recuperer dans la machine hote et qu'on execute notre programme on obtient une chaine de caractere qui va nous permettre d'acceder a l'utilisateur 'flag09'

```bash
➜  snowcrash scp -P 4243 level09@localhost:token .
➜  snowcrash ./decrypt $(cat token)
f3iji1ju5yuevaus41q1afiuq
```

```bash
level09@SnowCrash:~$ su flag09
Password: 
Don't forget to launch getflag !
flag09@SnowCrash:~$ getflag
Check flag.Here is your token : ******************
```
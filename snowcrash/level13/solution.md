# Level 13

```bash
level13@SnowCrash:~$ ls -l
total 8
-rwsr-sr-x 1 flag13 level13 7303 Aug 30  2015 level13
```

Si on l'execute on obtient ce resultat: 

```bash
level13@SnowCrash:~$ ./level13 
UID 2013 started us but we we expect 4242
```

Une fois l'executable dessassembler dans dogbolt on peut voir la fonction main qui ressemble a ceci:

```c
int32_t main(int32_t argc, char** argv, char** envp)
{
    if (getuid() == 0x1092)
        return printf("your token is %s\n", ft_des("boe]!ai0FB@.:|L6l@A?>qJ}I"));
    
    printf("UID %d started us but we we expect %d\n", getuid(), 0x1092);
    exit(1);
    /* no return */
}
```

On peut voir que le programme que nous ayons l'UID 4242 pour valider la condition et nous donner le token dechifrer avec la fonction 'ft_des'

Pour passer ce niveau nous devons:

	1- Set un breakpoint sur l'appel systeme 'getuid'
	2- 'finish' pour continuer l'execution de 'getuid' jusqu'a qu'il atteigne l'instruction 'ret'
	3- Ecraser la valeur de retour du registre eax avec la commande set $eax = 4242
	4- 'continue' pour executer la suite du programme

Puisque que la condition va etre valide on pourra voir le resultat de la fonction 'ft_des'

```bash
your token is *********************
level13@SnowCrash:~$ su level14
Password: 
level14@SnowCrash:~$
```
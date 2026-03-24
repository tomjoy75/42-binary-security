# Level 03

Pour ce niveau c'est encore une fois un niveau avec un programme qui demande un mot de passe a l'utilisateur qui calcul une difference entre notre mot de passe et une valeur ecrit en dur dans le code `322424845` dans la fonction `test` qui est le resultat de notre `key`

On sait grace au `switch case` que la valeur se situe entre `1` et `21` ensuite cette `key` est utilise comme `cle XOR` dans le `hash`

Notre objectif est donc de trouver cette valeur:

```
valeur = 322424845 - input

hash ^ valeur == "Congratulations!" 
```

Grace a notre petit programme ecrit en [C](./artifacts/xor_cipher.c) on reussi a trouver le mot de passe qui nous permettra d'executer un shell

```bash
➜  ressources git:(main) ✗ gcc xor_cipher.c -o xor && ./xor
Password is 322424827
```

```bash
level03@OverRide:~$ ./level03 
***********************************
*		level03		**
***********************************
Password:322424827  
$ whoami
level04
$ cat /home/users/level04/.pass
***************************************
$
```
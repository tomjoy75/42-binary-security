# Level 8

Apres analyse du binaire et de sa version desassemblee on observe que le programme lance un shell si la valeur situee `32 octets` après l’adresse retournee par le premier `malloc` (allocation de auth) est non nulle

Le programme propose une interface interactive avec plusieurs commandes notamment `auth` `service` et `login` qui permettent de manipuler des allocations sur la heap.

La commande auth alloue un petit chunk sur la heap.

La commande service utilise strdup, ce qui entraîne :

	-une nouvelle allocation sur la heap
	-l’ecriture d’une chaine entierement controlee par l’utilisateur

Dans la pratique, avec ce binaire et cet allocateur, le chunk alloue par service est place juste apres celui de auth

L’objectif est de rendre non nulle la valeur situee a l’adresse `auth + 32`
Pour cela :

	-On alloue d’abord le chunk auth
	-On appelle ensuite la commande service avec une chaine suffisamment longue

Les donnees ecrites par `strdup` occupent la memoire immediatement apres le chunk `auth` cette ecriture rend non nulle la zone memoire situee `32 octets` apres `auth` lorsque la commande login est executee la condition est satisfaite et le programme lance un shell

```bash
level8@RainFall:~$ ./level8 
(nil), (nil) 
auth 
0x804a008, (nil) 
service0123456789ABCDEF
0x804a008, 0x804a018 
login
$ whoami
level9
$ cat /home/user/level9/.pass
*********************************************
```
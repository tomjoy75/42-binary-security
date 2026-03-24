# Level 02

```bash
level02@SnowCrash:~$ ls
level02.pcap
```

On voit que dans ce niveau on a un fichier .pcap qui est un fichier "packet capture" d'un trafic reseau. On l'envoie par secure copy paste sur la machine hote

```bash
➜  snow_crash git:(main) ✗ scp -P 4243 level02@localhost:level02.pcap .
```

Puis on l'ouvre avec Wireshark pour analyser les paquets en fesant un clique droit -> Follow -> TCP Stream.
Nous pouvons suivre les datas envoyer par les differents paquets la partie qui nous interesse c'est la ligne

```
Password: ft_wandr...NDRel.L0L
```

En selectionnant HexDump dans la partie "Show Data as: " on peut voir que les caracteres representer par un "." sont le caractere DEL dans la table ASCII le mot de passe invalide devient donc "ft_waNDReL0L"

```bash
level02@SnowCrash:~$ su flag02
Password: 
Don't forget to launch getflag !
flag02@SnowCrash:~$ getflag
```
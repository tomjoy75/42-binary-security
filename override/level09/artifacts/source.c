#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char	msg[140];
	char	username[40];
	int	msg_len;
} msn;

void	secret_backdoor(void)
{
	char	backdoor[128];

	fgets(backdoor, 128, stdin);
	system(backdoor);
}

void	set_msg(msn *m)
{
	char	msg[1024];

	memset(msg, 0, sizeof(msg));
	puts(">: Msg @Unix-Dude");
	printf(">>: ");
	fgets(msg, 1024, stdin);
	strncpy(m->msg, msg, m->msg_len);
}

void	set_username(msn *m)
{
	char	name[140];

	memset(name, 0, 128);
	puts(">: Enter your username");
	printf(">>: ");
	fgets(name, 128, stdin);

	for (int i = 0; i <= 40 && name[i]; ++i)
		m->username[i] = name[i];
	
	printf(">: Welcome, %s", m->username);
}

void	handle_msg(void)
{
	msn	m;

	memset(m.username, 0, 40);
	m.msg_len = 140;

	set_username(&m);
	set_msg(&m);
	puts(">: Msg sent!");
}

int	main(void)
{
	puts(
	"--------------------------------------------\n"
	"|   ~Welcome to l33t-m$n ~    v1337        |\n"
	"--------------------------------------------");
	handle_msg();
	return 0;
}
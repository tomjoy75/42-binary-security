#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int	main(int argc, char **argv)
{
	if (atoi(argv[1]) == 423) {
		char	*exec[2] = {strdup("/bin/sh"), NULL};
		gid_t	gid = getegid();
		gid_t	uid = geteuid();

		setresgid(gid, gid, gid);
		setresuid(uid, uid, uid);
		execv("/bin/sh", exec);
	}
	
	fwrite("No !\n", sizeof(char), 5, stderr);
	return 0;
}
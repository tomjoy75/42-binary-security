#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

#define SYS_EXECVE 11

int	main(void)
{
	int	pid;
	int	status;
	long	syscall;
	char	buffer[128];

	pid = fork();
	memset(buffer, 0, sizeof(buffer));
	status = 0;
	
	if (pid == 0) {
		prctl(PR_SET_PDEATHSIG, SIGKILL);
		ptrace(PTRACE_TRACEME, 0, 0, 0);
		puts("Give me some shellcode, k");
		gets(buffer);
	} else {
		while (1) {
			wait(&status);
			if (WIFEXITED(status) || WIFSIGNALED(status)) {
				puts("child is exiting...");
				return 0;
			}
			syscall = ptrace(PTRACE_PEEKUSER, pid, 44, 0);
			if (syscall == SYS_EXECVE) {
				puts("no exec() for you");
				kill(pid, SIGKILL);
				return 0;
			}
		}
	}
	
	return 0;
}
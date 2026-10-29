#include <stdbool.h>
#include <stdio.h>      
#include <stdlib.h>     
#include <signal.h>     
#include <sys/types.h>  
#include <sys/wait.h>   
#include <errno.h>      
#include <string.h>     

static volatile sig_atomic_t g_timed_out = 0;
static volatile sig_atomic_t g_child_pid = -1;

static void	on_alarm(int sig)
{
	(void)sig;
	g_timed_out = 1;
	if (g_child_pid > 0)
		kill((pid_t)g_child_pid, SIGKILL);
}

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	struct sigaction old_alrm, sa;
	pid_t           pid;
	int             status;

	sa.sa_handler = on_alarm;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0; 
	if (sigaction(SIGALRM, &sa, &old_alrm) == -1)
		return (-1);

	pid = fork();
	if (pid < 0)
	{
		sigaction(SIGALRM, &old_alrm, NULL);
		return (-1);
	}
	if (pid == 0)
	{

		struct sigaction defsa;

		alarm(0);
		defsa.sa_handler = SIG_DFL;
		sigemptyset(&defsa.sa_mask);
		defsa.sa_flags = 0;
		sigaction(SIGALRM, &defsa, NULL);

		f();    
		exit(0);
	}


	g_child_pid = pid;
	g_timed_out = 0;
	if (timeout > 0)
		alarm(timeout);

	for (;;)
	{
		pid_t r = waitpid(pid, &status, 0);
		if (r == -1 && errno == EINTR)
			continue; 
		if (r == -1)
		{
			alarm(0);
			sigaction(SIGALRM, &old_alrm, NULL);
			return (-1);
		}
		break;
	}

	alarm(0);
	sigaction(SIGALRM, &old_alrm, NULL);

	if (g_timed_out)
	{
		if (verbose)
			printf("Bad function: timed out after %u seconds\n", timeout);
		return (0);
	}

	if (WIFEXITED(status))
	{
		int code = WEXITSTATUS(status);
		if (code == 0)
		{
			if (verbose)
				printf("Nice function!\n");
			return (1);
		}
		if (verbose)
			printf("Bad function: exited with code %d\n", code);
		return (0);
	}
	if (WIFSIGNALED(status))
	{
		int sig = WTERMSIG(status);
		if (verbose)
			printf("Bad function: %s\n", strsignal(sig));
		return (0);
	}
	if (WIFSTOPPED(status))
	{
		int sig = WSTOPSIG(status);
		if (verbose)
			printf("Bad function: %s\n", strsignal(sig));
		return (0);
	}
	return (-1);
}
#include <unistd.h>
#include <sys/types.h>  
#include <sys/wait.h>   

static void	close_safe(int *fd)
{
	if (*fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}

static void	close_pair(int *a, int *b)
{
	close_safe(a);
	close_safe(b);
}

static int	count_cmds(char **cmds[])
{
	int n;

	n = 0;
	if (!cmds)
		return (0);
	while (cmds[n])
		n++;
	return (n);
}

static void	wait_n_children(int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		wait(0);
		i++;
	}
}

int	picoshell(char **cmds[])
{
	int n, i, prev_read, pipefd[2], started;

	n = count_cmds(cmds);
	if (n <= 0)
		return (0);

	prev_read = -1;
	pipefd[0] = pipefd[1] = -1;
	started = i = 0;
	
	while (i < n)
	{
		if (i < n - 1)
		{
			if (pipe(pipefd) < 0)
			{
				close_safe(&prev_read);
				return (1);
			}
		}
		else
		{
			pipefd[0] = -1;
			pipefd[1] = -1;
		}
		{
			pid_t pid;
			pid = fork();
			if (pid < 0)
			{
				close_safe(&prev_read);
				close_pair(&pipefd[0], &pipefd[1]);
				if (started > 0)
					wait_n_children(started);
				return (1);
			}
			if (pid == 0)
			{
				if (prev_read >= 0)
				{
					if (dup2(prev_read, 0) < 0)
						exit(1);
				}
				if (pipefd[1] >= 0)
				{
					if (dup2(pipefd[1], 1) < 0)
						exit(1);
				}
				close_safe(&prev_read);
				close_pair(&pipefd[0], &pipefd[1]);
				execvp(cmds[i][0], cmds[i]);
				exit(1);
			}
			started++;
			close_safe(&prev_read);
			if (pipefd[1] >= 0)
				close_safe(&pipefd[1]);
			prev_read = pipefd[0];
			pipefd[0] = -1;
		}
		i++;
	}
	close_safe(&prev_read);
	wait_n_children(started);
	return (0);
}
#include <unistd.h> 
#include <stdlib.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (!file || !argv || !argv[0] || (type != 'r' && type != 'w'))
		return (-1);
	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		if (type == 'r' && dup2(pipe_fd[1], 1) == -1)
			exit(1);
		if (type == 'w' && dup2(pipe_fd[0], 0) == -1)
			exit(1);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execvp(file, argv);
		exit(1);
	}
	if (type == 'r')
	{
		close(pipe_fd[1]);
		return (pipe_fd[0]);
	}
	close(pipe_fd[0]);
	return (pipe_fd[1]);
}

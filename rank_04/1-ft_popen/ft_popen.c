/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 21:40:17 by nchairun          #+#    #+#             */
/*   Updated: 2026/03/12 21:40:19 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
    int     pipe_fd[2];
    pid_t   pid;

    if (!argv || !file || (type != 'r' && type != 'w'))
        return(-1);

    if (pipe(pipe_fd) == -1)
        return(-1);

    pid = fork();

    if (pid < 0)
    {
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return(-1);
    }

    if (pid == 0)
    {
        if (type == 'r' && dup2(pipe_fd[1], STDOUT_FILENO) == -1)
            exit(EXIT_FAILURE);
        if (type == 'w' && dup2(pipe_fd[0], STDIN_FILENO) == -1)
            exit(EXIT_FAILURE);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        execvp(file, argv);
        exit(EXIT_FAILURE);
    }

    if (type == 'r')
    {
        close(pipe_fd[1]);
        return(pipe_fd[0]);
    }

    close(pipe_fd[0]);
    return(pipe_fd[1]);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 05:51:42 by nchairun          #+#    #+#             */
/*   Updated: 2025/04/10 06:03:56 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *str)
{
	int		i = 0;
	char	*dest;

	while(str[i])
		i++;
	dest = malloc(i + 1);
	if (!dest)
		return(NULL);
	i = 0;
	while(str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return(dest);
}

char	*get_next_line(int fd)
{
	static int bytes_read = 0;
	static int buffer_pos = 0;
	static char buffer[BUFFER_SIZE];
	char line[7000000];
	int i = 0;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	while (1)
	{
		if (buffer_pos >= bytes_read)
		{
			bytes_read = read(fd,buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (bytes_read <= 0)
				break;
		}
		line[i++] = buffer[buffer_pos++];
		if (buffer[buffer_pos - 1] == '\n')
			break;
	}
    line[i] = '\0';
	if (i == 0)
		return(NULL);
	return(ft_strdup(line));
}

// int main(void)
// {
// 	int fd;
// 	char *line;

// 	fd = open("test.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		write(1, "Error opening file\n", 19);
// 		return (1);
// 	}
// 	while (line)
// 	{
// 		free(line);
// 		line = get_next_line(fd);
// 		if (line)
// 			printf("%s", line);
// 	}

// 	close(fd);
// 	return (0);
// }
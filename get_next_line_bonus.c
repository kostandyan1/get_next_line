/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:05:19 by vkostand          #+#    #+#             */
/*   Updated: 2024/03/01 22:46:58 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*remove_line(char *buffer)
{
	int		i;
	int		j;
	char	*without_line;	

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	i++;
	without_line = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!without_line)
		return (NULL);
	j = 0;
	while (buffer[i + j])
	{
		without_line[j] = buffer[i + j];
		j++;
	}
	without_line[j] = '\0';
	free(buffer);
	return (without_line);
}

static char	*get_new_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*read_line(int fd, char *buffer)
{
	char	*rd_line;
	int		bufsize;

	bufsize = 1;
	rd_line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!rd_line)
		return (NULL);
	while (bufsize > 0 && !ft_strchr(buffer, '\n'))
	{
		bufsize = read(fd, rd_line, BUFFER_SIZE);
		if (bufsize < 0)
		{
			free(rd_line);
			return (NULL);
		}
		rd_line[bufsize] = '\0';
		buffer = ft_join(buffer, rd_line);
	}
	free(rd_line);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE < 1)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = read_line(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = get_new_line(buffer[fd]);
	buffer[fd] = remove_line(buffer[fd]);
	if (*line == '\0')
	{
		free(line);
		free(buffer[fd]);
		buffer[fd] = NULL;
		line = NULL;
	}
	return (line);
}

// int main()
// {
//     int fd1;
//     int fd2;

//     fd1 = open("test1.txt", O_RDWR);
//     fd2 = open("test2.txt", O_RDWR);
//     printf("%s", get_next_line_bonus())
//     printf("%s",)
// }

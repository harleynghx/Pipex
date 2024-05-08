/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hang <hang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 08:32:48 by hang              #+#    #+#             */
/*   Updated: 2024/05/08 17:17:55 by hang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*cleanline(char *fd_str)
{
	int		i;
	char	*str;

	i = 0;
	if (!fd_str[i])
		return (NULL);
	while (fd_str[i] && fd_str[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (fd_str[i] && fd_str[i] != '\n')
	{
		str[i] = fd_str[i];
		i++;
	}
	if (fd_str[i] == '\n')
	{
		str[i] = fd_str[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*delete_upto_nl(char *fd_str)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (fd_str[i] && fd_str[i] != '\n')
		i++;
	if (!fd_str[i])
	{
		free(fd_str);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(fd_str) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (fd_str[i])
		str[j++] = fd_str[i++];
	str[j] = '\0';
	free(fd_str);
	return (str);
}

char	*readnjoin(int fd, char *fd_str)
{
	char	*buff;
	int		read_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(fd_str, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		fd_str = ft_strjoin(fd_str, buff);
	}
	free(buff);
	return (fd_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*fd_str[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	fd_str[fd] = readnjoin(fd, fd_str[fd]);
	if (!fd_str[fd])
		return (NULL);
	line = cleanline(fd_str[fd]);
	fd_str[fd] = delete_upto_nl(fd_str[fd]);
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hang <hang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:03:04 by hang              #+#    #+#             */
/*   Updated: 2024/04/23 18:17:45 by hang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <stdio.h>

void	inproper_args(void)
{
	ft_putstr_fd("\033[31mError: \033[33mInproper Arguments\n\033[0m", 2);
	ft_putstr_fd("\033[33mEx: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n", 1);
	ft_putstr_fd("    ./pipex \"here_doc\" <LIMITER> <cmd> <cmd1> <...> <file>\n", 1);
	exit(EXIT_SUCCESS);
}

// int	ft_get_terminal_output(char **line)
// {
// 	char	*buffer;
// 	int		i;
// 	int		r;
// 	char	letter;

// 	i = 0;
// 	r = 0;
// 	buffer = (char *)malloc(10000);
// 	if (!buffer)
// 		return (-1);
// 	r = read(0, &letter, 1);
// 	while (r && letter != '\n' && letter != '\0')
// 	{
// 		if (letter != '\n' && letter != '\0')
// 			buffer[i] = letter;
// 		i++;
// 		r = read(0, &letter, 1);
// 	}
// 	buffer[i] = '\n';
// 	buffer[++i] = '\0';
// 	*line = buffer;
// 	free(buffer);
// 	return (r);
// }


int	ft_get_terminal_output(char **line)
{
	char	*buffer;
	int		i;
	char	letter;

	i = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	read(0, &letter, 1);
	while (letter != '\n' && letter != '\0')
	{
		if (letter != '\n' && letter != '\0')
			buffer[i] = letter;
		i++;
		read(0, &letter, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (1);
}

void	here_doc(char *limiter, int argc)
{
	pid_t	pid;
	int		fd[2];
	char	*line;

	if (argc < 6)
		inproper_args();
	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (ft_get_terminal_output(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

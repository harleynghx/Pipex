/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hang <hang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:24:37 by hang              #+#    #+#             */
/*   Updated: 2024/05/08 17:26:13 by hang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char *cmd_args, char **envp)
{
	char	**split_paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	split_paths = ft_split(envp[i], ':');
	i = 0;
	while (split_paths[i])
	{
		part_path = ft_strjoin(split_paths[i], "/");
		path = ft_strjoin(part_path, cmd_args);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (split_paths[++i])
		free(split_paths[i]);
	free(split_paths);
	return (0);
}

void	execute(char *argv, char **envp)
{
	char	**cmd_args;
	int		i;
	char	*split_path;

	i = -1;
	cmd_args = ft_split(argv, ' ');
	split_path = find_path(cmd_args[0], envp);
	if (!split_path)
	{
		while (cmd_args[++i])
			free(cmd_args[i]);
		free(cmd_args);
		error();
	}
	if (execve(split_path, cmd_args, envp) == -1)
		error();
}

void	inproper_args(void)
{
	ft_putstr_fd("\033[31mError: \033[33mInproper Arguments\n\033[0m", 2);
	ft_putstr_fd("\033[33mEx: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n",
		1);
	exit(EXIT_SUCCESS);
}

int	gnl(char **line)
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
		while (gnl(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		waitpid(-1, NULL, 0);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

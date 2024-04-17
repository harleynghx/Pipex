/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hang <hang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:24:37 by hang              #+#    #+#             */
/*   Updated: 2024/04/17 15:11:13 by hang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/* To search through all the path for the command. Check note for more info */
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

/* A simple error displaying function. */
void	error(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

/* Function that take the command and send it to find_path
 before executing it. */
void	execute(char *argv, char **envp)
{
	char	**cmd_args;
	int 	i;
	char	*split_path;
	
	i = -1;
	cmd_args = ft_split(argv, ' ');
	split_path = find_path(cmd_args[0], envp);

	//to free it if variable == falsy
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
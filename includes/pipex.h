/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hang <hang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:59:05 by hang              #+#    #+#             */
/*   Updated: 2024/04/17 15:11:42 by hang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"

void    child_p(char **argv, char **envp, pid_t *pipe_fd);
void    parent_p(char **argv, char **envp, pid_t *pipe_fd);
void	error(void);
char	*find_path(char *cmd, char **envp);
void	execute(char *argv, char **envp);

#endif
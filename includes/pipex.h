/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hang <hang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:59:05 by hang              #+#    #+#             */
/*   Updated: 2024/05/08 03:17:11 by hang             ###   ########.fr       */
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

char	*find_path(char *cmd, char **envp);
void	execute(char *argv, char **envp);

void	error(void);
void	inproper_args(void);
int	    GNL(char **line);
void	here_doc(char *limiter, int argc);
#endif
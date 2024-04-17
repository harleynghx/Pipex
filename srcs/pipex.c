/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hang <hang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:24:35 by hang              #+#    #+#             */
/*   Updated: 2024/04/17 15:22:32 by hang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

//objective for main function is to pipe and fork.

void    child_p(char **argv, char **envp, pid_t *pipe_fd)
{
    int infile_fd;
    
    infile_fd = open(argv[1] ,O_RDONLY, 0777);
    if(infile_fd == -1)
        error();
    dup2(infile_fd, STDIN_FILENO);
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[0]);
    execute(argv[2], envp);
    /*execute argv[1] with the first command */
}

void    parent_p(char **argv, char **envp, pid_t *pipe_fd)
{
	int		outfile_fd;

	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile_fd == -1)
		error();
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(pipe_fd[1]);
	execute(argv[3], envp);
}
int main(int argc, char **argv, char **envp)
{
    int pipe_fd[2];
    pid_t pid;
    if (argc == 5)
    {
        if (pipe(pipe_fd) == -1)
            error();
        pid = fork();
        if (pid == 0)
            child_p(argv, envp, pipe_fd);
        waitpid(pid, NULL, 0);
        parent_p(argv, envp, pipe_fd);
    }
    else
	{
		ft_putstr_fd("\033[31mError: \033[33mInproper Arguments\n\033[0m", 2);
		ft_putstr_fd("\033[33mE.g. : ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
	return (0);
}
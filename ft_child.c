/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:00:34 by anboisve          #+#    #+#             */
/*   Updated: 2023/03/13 14:49:39 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid
*/

void	run_cmd(char *cmd, char **path)
{
	char	**argv;
	char	*run;

	run = NULL;
	argv = NULL;
	argv = ft_split(cmd, ' ');
	run = ft_find_cmd(argv[0], path);
	if (run)
		execve(run, argv, path);
	ft_safe_free(run);
	ft_double_sfree((void **)argv);
	perror(sys_errlist[sys_nerr]);
	exit(errno);
}

void	child(t_pipex *data, char *cmd)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		waitpid(pid, NULL, WNOHANG);
	}
	else
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		run_cmd(cmd, data->path);
		ft_free_data(data);
	}
}

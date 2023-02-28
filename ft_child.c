/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:00:34 by anboisve          #+#    #+#             */
/*   Updated: 2023/02/28 12:48:56 by anboisve         ###   ########.fr       */
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

	argv = ft_split(cmd, ' ');
	run = ft_find_cmd(argv[0], path);
	if (execve(run, argv, path))
	{
		ft_safe_free(run);
		ft_double_sfree((void **)argv);
		perror(sys_errlist[sys_nerr]);
		exit(sys_nerr);
	}
}

void	child(t_pipex *data, char *cmd, int fdin)
{
	pid_t	pid;
	int		fd[2];

	(void)fdin;
	pipe(fd);
	pid = fork();
	if (pid)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		run_cmd(cmd, data->path);
	}
}

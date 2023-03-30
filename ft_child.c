/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:00:34 by anboisve          #+#    #+#             */
/*   Updated: 2023/03/30 17:42:12 by anboisve         ###   ########.fr       */
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
	perror(argv[0]);
	ft_safe_free(run);
	ft_double_sfree((void **)argv);
	exit(1);
}

void	child(t_pipex *data, char *cmd, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid)
	{
		dup2(data->fds[i][0], STDIN_FILENO);
		close(data->fds[i][0]);
		close(data->fds[i][1]);
		waitpid(pid, NULL, WNOHANG);
		ft_printf("here\n");
	}
	else
	{
		dup2(data->fds[i][1], STDOUT_FILENO);
		close(data->fds[i][0]);
		close(data->fds[i][1]);
		run_cmd(cmd, data->path);
		ft_free_data(data);
		ft_printf("here2\n");
	}
}

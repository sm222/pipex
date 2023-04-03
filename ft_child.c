/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:00:34 by anboisve          #+#    #+#             */
/*   Updated: 2023/04/03 17:45:00 by anboisve         ###   ########.fr       */
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

void	run_cmd(char *cmd, char **path, t_pipex *data)
{
	char	**argv;
	char	*run;

	run = NULL;
	argv = NULL;
	argv = ft_str_split(cmd, ft_split("''* *\"\"*()*<>", '*'));
	if (!argv)
		ft_free_data(data);
	run = ft_find_cmd(argv[0], path);
	ft_close_fds(data->fds, 0);
	if (run)
		execve(run, argv, path);
	perror(argv[0]);
	ft_safe_free(run);
	ft_double_sfree((void **)argv);
	ft_free_data(data);
	exit(1);
}

void	child(t_pipex *data, char *cmd, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid)
	{
		if (i == 0)
		{
			dup2(data->input, STDIN_FILENO);
			close(data->input);
		}
		else
		{
			dup2(data->fds[i][0], STDIN_FILENO);
			close(data->fds[i][0]);
		}
		close(data->fds[i][1]);
		if (i != 0)
		{
			if (!make_pid_node(&data->pids, pid))
				ft_error("malloc fail", data);
		}
	}
	else
	{
		if (i == data->argc - 3)
		{
			dup2(data->output, STDOUT_FILENO);
			close(data->output);
		}
		else
		{
			dup2(data->fds[i][1], STDOUT_FILENO);
			close(data->fds[i][1]);
		}
		close(data->fds[i][0]);
		if (i != 0)
			run_cmd(cmd, data->path, data);
		ft_free_data(data);
	}
}

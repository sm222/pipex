/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:00:34 by anboisve          #+#    #+#             */
/*   Updated: 2023/04/18 17:53:45 by anboisve         ###   ########.fr       */
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

void	first(t_pipex *data, int *fd)
{
	pid_t	pid;
	
	pipe(fd);
	pid = fork();
	if (pid < 0)
		ft_exit(data, errno, "first");
	if (pid)
	{
		if (!make_pid_node(&data->pids, pid))
		{
			data->pids = NULL;
			ft_exit(data, 1, "malloc fail make_pid_node");
		}
	}
	else
	{
		dup2(data->input, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(data->input);
		close(fd[0]);
		close(fd[1]);
		run_cmd(data->argv[2], data->path, data);
	}
}

void	mid(t_pipex *data, int *fd, int index)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_exit(data, errno, "last");
	if (pid)
	{
		if (!make_pid_node(&data->pids, pid))
		{
			data->pids = NULL;
			ft_exit(data, 1, "malloc fail make_pid_node");
		}
	}
	else
	{
		if (index % 2 == 0)
		{
			dup2(fd[3], STDIN_FILENO);
			dup2(fd[2], STDOUT_FILENO);
			close(fd[3]);
			close(fd[2]);
			///
		}
		else
		{
			dup2(fd[0], STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
		}
		run_cmd(data->argv[index + 2], data->path, data);
	}
}

void	last(t_pipex *data, int *fd, int index)
{
	pid_t	pid;
	
	pid = fork();
	if (pid < 0)
		ft_exit(data, errno, "last");
	if (pid)
	{
		if (!make_pid_node(&data->pids, pid))
		{
			data->pids = NULL;
			ft_exit(data, 1, "malloc fail make_pid_node");
		}
	}
	else
	{
		dup2(data->output, STDOUT_FILENO);
		if (index % 2 == 0)
		{
			dup2(fd[2], STDIN_FILENO);
			close(fd[2]);
			ft_putendl_fd("last", 2);
		}
		else
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			ft_putendl_fd("last2", 2);
		}
		close(data->output);
		run_cmd(data->argv[index + 2], data->path, data);
	}
}
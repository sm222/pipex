/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:00:34 by anboisve          #+#    #+#             */
/*   Updated: 2023/04/21 11:20:36 by anboisve         ###   ########.fr       */
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

void	first(t_pipex *data, int fd_i, int index)
{
	pid_t	pid;

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
		dup2(data->pipes[fd_i][1], STDOUT_FILENO);
		close(data->input);
		close(data->output);
		ft_close_fds(data->pipes, 1, data->nbr_cmd);
		run_cmd(data->argv[index], data->path, data);
	}
}

void	mid(t_pipex *data, int fd_i, int index)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_exit(data, errno, "mid");
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
		ft_putnbr_fd(data->nbr_cmd, 2);
		ft_putendl_fd(data->argv[index], 2);
		dup2(data->pipes[fd_i][0], STDIN_FILENO);
		if (index == data->argc - 2)
		{
			dup2(data->output, STDOUT_FILENO);
			ft_putchar_fd('%', 2);
		}
		else
			dup2(data->pipes[fd_i + 1][1], STDOUT_FILENO);
		close(data->input);
		close(data->output);
		ft_close_fds(data->pipes, 1, data->nbr_cmd);
		run_cmd(data->argv[index], data->path, data);
	}
}

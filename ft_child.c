/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:00:34 by anboisve          #+#    #+#             */
/*   Updated: 2023/04/23 11:09:51 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
run the first commander and set the input on the choose file
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
		run_cmd(data->argv[index], data->path, data);
	}
}

/*
run the rest of the command and switch for the outfile on the last one
*/
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
		dup2(data->pipes[fd_i][0], STDIN_FILENO);
		if (index == data->argc - 2)
			dup2(data->output, STDOUT_FILENO);
		else
			dup2(data->pipes[fd_i + 1][1], STDOUT_FILENO);
		close(data->input);
		close(data->output);
		run_cmd(data->argv[index], data->path, data);
	}
}

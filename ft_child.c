/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:00:34 by anboisve          #+#    #+#             */
/*   Updated: 2023/02/23 17:53:42 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child1(t_pipex *data)
{
	char	*cmd;

	if (dup2(data->input, STDIN_FILENO) < 0)
		ft_error(sys_errlist[sys_nerr], data);
	if (dup2(data->pipe[1], STDOUT_FILENO) < 0)
		ft_error(sys_errlist[sys_nerr], data);
	data->cmd1 = ft_split(data->argv[2], ' ');
	cmd = ft_find_cmd(data->cmd1[0], data);
	close(data->pipe[0]);
	close(data->pipe[1]);
	if (execve(cmd, data->cmd1, data->en) == -1)
	{
		ft_free_data(data);
		ft_safe_free(cmd);
		exit(sys_nerr);
	}
	ft_free_data(data);
	ft_safe_free(cmd);
	exit(0);
}

void	ft_mid_child(t_pipex *data, int cmd_index)
{
	char	*cmd;
	char	**cmd_split;

	if (dup2(data->output, STDOUT_FILENO) < 0)
		ft_error(sys_errlist[sys_nerr], data);
	if (dup2(data->pipe[0], STDIN_FILENO) < 0)
		ft_error(sys_errlist[sys_nerr], data);
	cmd_split = ft_split(data->argv[cmd_index], ' ');
	cmd = ft_find_cmd(data->cmd2[0], data);
	close(data->pipe[0]);
	close(data->pipe[1]);
	if (execve(cmd, cmd_split, data->en) == -1)
	{
		ft_free_data(data);
		ft_safe_free(cmd);
		ft_double_sfree((void **)cmd_split);
		exit(sys_nerr);
	}
	ft_safe_free(cmd);
	ft_double_sfree((void **)cmd_split);
	exit(0);
}

void	ft_child2(t_pipex *data)
{
	char	*cmd;

	if (dup2(data->output, STDOUT_FILENO) < 0)
		ft_error(sys_errlist[sys_nerr], data);
	if (dup2(data->pipe[0], STDIN_FILENO) < 0)
		ft_error(sys_errlist[sys_nerr], data);
	data->cmd2 = ft_split(data->argv[3], ' ');
	cmd = ft_find_cmd(data->cmd2[0], data);
	close(data->pipe[0]);
	close(data->pipe[1]);
	if (execve(cmd, data->cmd2, data->en) == -1)
	{
		ft_free_data(data);
		ft_safe_free(cmd);
		exit(sys_nerr);
	}
	ft_free_data(data);
	ft_safe_free(cmd);
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:00:34 by anboisve          #+#    #+#             */
/*   Updated: 2023/02/26 17:56:19 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_cmd(t_pipex *data, int i)
{
	char	*cmd;
	char	**cmd_split;

	cmd_split = ft_split(data->argv[i], ' ');
	cmd = ft_find_cmd(cmd_split[0], data);
	if (execve(cmd, cmd_split, data->en) == -1)
	{
		ft_free_data(data);
		ft_safe_free(cmd);
		ft_double_sfree((void **)cmd_split);
		exit(sys_nerr);
	}
}

void	ft_mid_child(t_pipex *data, int mode, int i)
{
	pid_t	pid;
	int		fd[2];

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
		dup2(fd[0], STDOUT_FILENO);
		if (mode == STDIN_FILENO)
			exit(1);
		else
			run_cmd(data, i);
	}
}

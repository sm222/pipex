/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:00:34 by anboisve          #+#    #+#             */
/*   Updated: 2023/02/21 10:09:25 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child1(t_pipex *data)
{
	char	*p;

	dup2(data->input, STDIN_FILENO);
	dup2(data->pipe[1], STDOUT_FILENO);
	close(data->pipe[0]);
	close(data->pipe[1]);
	p = ft_find_cmd(data->cmd1[0], data);
	if (execve(p, data->cmd1, data->en) == -1)
	{
		ft_free_data(data);
		ft_safe_free(p);
		exit(sys_nerr);
	}
	exit(0);
}

void	ft_child2(t_pipex *data)
{
	char	*p;

	dup2(data->output, STDOUT_FILENO);
	dup2(data->pipe[0], STDIN_FILENO);
	close(data->pipe[0]);
	close(data->pipe[1]);
	p = ft_find_cmd(data->cmd2[0], data);
	if (execve(p, data->cmd2, data->en) == -1)
	{
		ft_free_data(data);
		ft_safe_free(p);
		exit(sys_nerr);
	}
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 09:33:16 by anboisve          #+#    #+#             */
/*   Updated: 2023/04/21 17:10:27 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
open, close, read, write,
malloc, free, perror,,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid
*/

static void	set_data(t_pipex *data, int ac, char **av, char **en)
{
	data->argc = ac;
	data->argv = av;
	data->en = en;
	data->input = open(av[1], O_RDONLY);
	data->output = \
	open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->output < 0)
		ft_exit(data, errno, av[ac - 1]);
	if (data->input < 0)
		ft_exit(data, errno, av[1]);
}

void	pipex(t_pipex *data)
{
	int	cmd;

	data->i = 0;
	cmd = 3;
	data->path = ft_make_path(data);
	first(data, 0, 2);
	while (cmd < data->argc - 1)
	{
		mid(data, data->i, cmd);
		data->i++;
		cmd++;
	}
	ft_close_fds(data->pipes, 1, data->nbr_pipes);
	close(data->input);
	close(data->output);
}

int	main(int ac, char **av, char **en)
{
	t_pipex	data;

	ft_bzero(&data, sizeof(t_pipex));
	if (ac != 5)
		return (1);
	set_data(&data, ac, av, en);
	data.nbr_pipes = make_pipes(ac - 3, &data.pipes);
	if (data.nbr_pipes == -1)
		ft_exit(&data, errno, "make_pipes");
	pipex(&data);
	wait_node(&data.pids);
	return (0);
}

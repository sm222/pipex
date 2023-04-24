/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 09:33:16 by anboisve          #+#    #+#             */
/*   Updated: 2023/04/24 12:25:47 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
set the variable to the rigth value
and open the infile and outfile
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

/*
run all the comments
*/
void	pipex(t_pipex *data)
{
	data->i = 0;
	data->cmd = 2;
	data->path = ft_make_path(data);
	if (!data->path)
		ft_exit(data, 1, "can't find PATH");
	first(data, data->i, data->cmd++);
	while (data->cmd < data->argc - 1)
		mid(data, data->i++, data->cmd++);
	ft_close_fds(data->pipes, 1, data->nbr_pipes);
	ft_double_sfree((void **)data->path);
	close(data->input);
	close(data->output);
}

/*
call the 4 main fontion

set_data, put the rigth value in the variable

make_pipes, open the rigth ammont of pipe

pipex, the one runing the commands and redirecting the data

wait_node, making sure all commande finish runing before ending the programe

*/
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

/*
External functions

open, close, read, write,
malloc, free, perror,,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid
*/
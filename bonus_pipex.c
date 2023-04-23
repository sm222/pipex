/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:10:03 by anboisve          #+#    #+#             */
/*   Updated: 2023/04/23 11:24:23 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
set the variable to the right value.
if the here_doc is user, it will change the flag to not clean the outfile
and call the fontion here_doc
*/
static void	set_data(t_pipex *data, int ac, char **av, char **en)
{
	int	flag;

	data->argc = ac;
	data->argv = av;
	data->en = en;
	if (!data->here_doc)
	{
		data->input = open(av[1], O_RDONLY);
		flag = O_TRUNC;
	}
	else
	{
		flag = O_APPEND;
		here_doc(data);
	}
	data->output = \
	open(av[ac - 1], O_RDWR | O_CREAT | flag, 0644);
	if (data->output < 0)
		ft_exit(data, errno, av[ac - 1]);
	if (data->input < 0)
		ft_exit(data, errno, av[1]);
}

/*
run all the commende and remove the here_doc file at the end
*/
void	pipex_bonus(t_pipex *data)
{
	data->cmd += 2;
	data->path = ft_make_path(data);
	if (!data->path)
		ft_exit(data, 1, "can't find PATH");
	first(data, data->i, data->cmd++);
	while (data->cmd < data->argc - 1)
		mid(data, data->i++, data->cmd++);
	ft_close_fds(data->pipes, 1, data->nbr_pipes);
	close(data->input);
	close(data->output);
	if (data->here_doc)
		if (unlink("/tmp/here_doc") == -1)
			perror("pipex_bonus");
}

/*
call the 4 main fontion
// allso look if the user want to use here_doc

set_data, put the rigth value in the variable

make_pipes, open the rigth ammont of pipe

pipex, the one runing the commands and redirecting the data

wait_node, making sure all commande finish runing before ending the programe

*/
int	main(int ac, char **av, char **en)
{
	t_pipex	data;

	ft_bzero(&data, sizeof(t_pipex));
	if (ac < 4)
		return (1);
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		if (ac > 5)
		{
			data.cmd++;
			data.i++;
			data.here_doc = 1;
		}
		else
			return (1);
	}
	set_data(&data, ac, av, en);
	data.nbr_pipes = make_pipes(ac - 3, &data.pipes);
	pipex_bonus(&data);
	wait_node(&data.pids);
	return (0);
}

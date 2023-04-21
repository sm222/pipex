/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:10:03 by anboisve          #+#    #+#             */
/*   Updated: 2023/04/21 18:02:13 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	set_data(t_pipex *data, int ac, char **av, char **en)
{
	data->argc = ac;
	data->argv = av;
	data->en = en;
	if (!data->here_doc)
		data->input = open(av[1], O_RDONLY);
	else
		here_doc(data);
	data->output = \
	open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->output < 0)
		ft_exit(data, errno, av[ac - 1]);
	if (data->input < 0)
		ft_exit(data, errno, av[1]);
}

void	pipex_bonus(t_pipex *data)
{
	int	cmd;

	data->i = 0;
	cmd = 3;
	data->path = ft_make_path(data);
	first(data, data->i, cmd++);
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
	if (ac < 4)
		return (1);
	//if (ft_strncmp(av[1], "here_doc", 9) == 0)
	//{
	//	if (ac > 5)
	//		data.here_doc = 1;
	//	else
	//		return (1);
	//}
	set_data(&data, ac, av, en);
	data.nbr_pipes = make_pipes(ac - 3, &data.pipes);
	pipex_bonus(&data);
	wait_node(&data.pids);
	return (0);
}

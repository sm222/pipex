/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:10:03 by anboisve          #+#    #+#             */
/*   Updated: 2023/02/19 17:51:18 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	void	ft_free_data(t_pipex *data)
{
	ft_double_sfree((void **)data->path);
	ft_double_sfree((void **)data->cmd1);
	ft_double_sfree((void **)data->cmd2);
}

static void	ft_start_data(t_pipex *data, char **av, char **en)
{
	data->argv = av;
	data->en = en;
	data->path = ft_make_path(en);
	ft_chek_file(data);
	ft_chek_cmd(data);
}

int	main(int ac, char **av, char **en)
{
	t_pipex	data;

	if (ac == 5)
	{
		ft_start_data(&data, av, en);
		if (pipe(&data.pipe[0]) != 0)
			ft_error("can't make the pipe");
		data.pid[0] = fork();
		if (data.pid[0] == 0)
			ft_child1(&data);
		close(data.pipe[1]);
		data.pid[1] = fork();
		if (data.pid[1] == 0)
			ft_child2(&data);
		close(data.pipe[0]);
		waitpid(data.pid[0], NULL, 0);
		waitpid(data.pid[1], NULL, 0);
		ft_free_data(&data);
	}
	else
		ft_error("need 4 argv");
	return (0);
}

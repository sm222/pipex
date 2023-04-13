/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:10:03 by anboisve          #+#    #+#             */
/*   Updated: 2023/04/13 16:47:32 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_start_data(t_pipex *data, int ac, char **av, char **en)
{
	data->argv = av;
	data->en = en;
	data->argc = ac;
	data->path = ft_make_path(data);
	ft_check_file(data);
	data->fds = ft_calloc(--ac, sizeof(int *));
	if (!data->fds)
		ft_error("ft_calloc", data);
	while (ac-- - 1)
	{
		data->fds[ac - 1] = ft_calloc(2, sizeof(int));
		if (!data->fds[ac - 1])
			ft_error("ft_calloc", data);
		if (pipe(data->fds[ac - 1]) == -1)
			ft_error("pipe", data);
	}
}

int	main(int ac, char **av, char **en)
{
	t_pipex	data;
	t_pids	*tmp;

	ft_bzero(&data, sizeof(t_pipex));
	if (ac < 4)
		ft_error("format: infile  cmd > 1  outfile", NULL);
	ft_start_data(&data, ac, av, en);
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		here_doc(&data);
	while (data.i < ac - 2)
		task(&data, av[1 + data.i++], data.j++);
	tmp = data.pids;
	while (tmp)
	{
		waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
	ft_free_data(&data);
	return (0);
}

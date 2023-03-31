/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:10:03 by anboisve          #+#    #+#             */
/*   Updated: 2023/03/31 09:16:37 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_start_data(t_pipex *data, int ac, char **av, char **en)
{
	ft_bzero(data, sizeof(t_pipex));
	data->argv = av;
	data->en = en;
	data->argc = ac;
	data->path = ft_make_path(data);
	ft_check_file(data);
	data->fds = ft_calloc(--ac, sizeof(int *));
	if (!data->fds)
		exit(ft_printf("EXIT_MALLOC\n"));
	while (ac-- - 1)
	{
		data->fds[ac - 1] = ft_calloc(2, sizeof(int));
		if (!data->fds[ac - 1])
			exit(ft_printf("EXIT_MALLOC2\n"));
		if (pipe(data->fds[ac - 1]) == -1)
			exit(ft_printf("EXIT_PIPE\n"));
	}
}

int	main(int ac, char **av, char **en)
{
	t_pipex	data;
	int		i;

	i = 0;
	if (ac < 4)
		exit(ft_printf("EXIT\n"));
	ft_start_data(&data, ac, av, en);
	while (i < ac - 2)
	{
		child(&data, av[i + 1], i);
		i++;
	}
	return (0);
}

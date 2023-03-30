/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:10:03 by anboisve          #+#    #+#             */
/*   Updated: 2023/03/30 11:23:27 by anboisve         ###   ########.fr       */
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
}

int	main(int ac, char **av, char **en)
{
	t_pipex	data;

	if (ac < 5)
		exit(ft_printf("EXIT\n"));
	ft_start_data(&data, ac, av, en);
	data.fds = ft_calloc(--ac, sizeof(int *));
	while (ac-- - 1)
	{
		data.fds[ac - 1] = ft_calloc(2, sizeof(int));
		pipe(data.fds[ac - 1]);
	}
	ft_printf("%d\n", ft_close_fds(data.fds, 1));
	return (0);
}

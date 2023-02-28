/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:10:03 by anboisve          #+#    #+#             */
/*   Updated: 2023/02/28 15:43:37 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_start_data(t_pipex *data, int ac, char **av, char **en)
{
	data->argv = av;
	data->en = en;
	data->argc = ac;
	data->path = ft_make_path(data);
	ft_check_file(data);
}

int	main(int ac, char **av, char **en)
{
	t_pipex	data;
	int		i;

	i = 3;
	data.path = NULL;
	if (ac >= 5)
	{
		ft_start_data(&data, ac, av, en);
		dup2(data.input, STDIN_FILENO);
		dup2(data.output, STDOUT_FILENO);
		child(&data, av[2], data.input);
		while (i < ac - 2)
			child(&data, av[i++], 1);
		run_cmd(av[i], data.path);
		ft_double_sfree((void **)data.path);
	}
	else
		ft_error("need 4 argv or more", &data);
	return (0);
}

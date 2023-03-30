/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:10:03 by anboisve          #+#    #+#             */
/*   Updated: 2023/03/30 17:56:57 by anboisve         ###   ########.fr       */
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
	dup2(data->input, STDIN_FILENO);
	dup2(data->output, STDOUT_FILENO);
}

void	make_fork(t_pids *data)
{
	(void)data;
}

int	main(int ac, char **av, char **en)
{
	t_pipex	data;
	int		i;

	i = 0;
	if (ac < 5)
		exit(ft_printf("EXIT\n"));
	ft_start_data(&data, ac, av, en);
	dup2(STDIN_FILENO, data.fds[0][0]);
	while (i < ac - 2)
	{
		child(&data, "ls", i++);
		
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:49:44 by anboisve          #+#    #+#             */
/*   Updated: 2023/03/27 14:09:25 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//285 bytes in 12 blocks

void	ft_start_data(t_pipex *data, int ac, char **av, char **en)
{
	data->argv = av;
	if (!en)
		ft_error("can't find enviroment", NULL);
	data->en = en;
	data->argc = ac;
	data->path = ft_make_path(data);
	ft_check_file(data);
}

int	main(int ac, char **av, char **en)
{
	t_pipex		data;

	ft_bzero(&data, sizeof(t_pipex));
	data.path = NULL;
	if (ac == 5)
	{
		ft_start_data(&data, ac, av, en);
		dup2(data.input, STDIN_FILENO);
		dup2(data.output, STDOUT_FILENO);
		close(data.input);
		close(data.output);
		child(&data, av[2]);
		run_cmd(av[3], data.path);
		ft_free_data(&data);
	}
	else
		ft_error("infile ,cmd1 cmd2 outfile ", &data);
	return (EXIT_SUCCESS);
}

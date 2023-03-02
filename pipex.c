/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:49:44 by anboisve          #+#    #+#             */
/*   Updated: 2023/03/02 15:37:06 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//285 bytes in 12 blocks

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
	t_pipex		data;

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
		ft_error("only take 2 file and 2 cmd", &data);
	return (EXIT_SUCCESS);
}

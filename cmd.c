/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:38:29 by anboisve          #+#    #+#             */
/*   Updated: 2023/04/21 16:07:25 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_cmd(char *cmd, char **path, t_pipex *data)
{
	char	**argv;
	char	**list;
	char	*run;

	run = NULL;
	argv = NULL;
	list = NULL;
	ft_close_fds(data->pipes, 1, data->nbr_pipes);
	list = ft_split("*''* *\"\"*	", '*');
	if (list)
	{
		argv = ft_str_split(cmd, list);
		if (!argv)
			ft_exit(data, 1, "malloc in ft_str_split");
		run = ft_find_cmd(argv[0], path);
		execve(run, argv, path);
	}
	else
		ft_exit(data, 1, "malloc in ft_split");
	perror(argv[0]);
	ft_safe_free(run);
	ft_double_sfree((void **)argv);
	ft_double_sfree((void **)list);
	exit(1);
}

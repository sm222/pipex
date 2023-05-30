/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:38:29 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/16 17:49:52 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
take the cmd, path and structure and try to run the bash command
if it fail, it free all the data inside
*/
void	run_cmd(char *cmd, char **path, t_pipex *data)
{
	char	**argv;
	char	**list;
	char	*run;

	run = NULL;
	argv = NULL;
	list = NULL;
	ft_close_fds(data->pipes, 1, data->nbr_pipes);
	data->pipes = NULL;
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
	ft_exit(data, errno, NULL);
}

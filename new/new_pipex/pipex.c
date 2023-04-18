/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 09:33:16 by anboisve          #+#    #+#             */
/*   Updated: 2023/04/18 17:51:35 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
open, close, read, write,
malloc, free, perror,,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid
*/

void	ft_exit(t_pipex *data, int err, char *msg)
{
	(void)data;
	perror(msg);
	exit(err);
}

void	set_data(t_pipex *data, int ac, char **av, char **en)
{
	data->argc = ac;
	data->argv = av;
	data->en = en;
	if (!data->here_doc)
		data->input = open(av[1], O_RDONLY);
	data->output = \
	open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->output < 0)
		ft_exit(data, errno, av[ac - 1]);
	if (data->input < 0)
		ft_exit(data, errno, av[1]);
}

void	pipex(t_pipex *data)
{
	int	fd[4];
	int	i;

	i = 0;
	data->path = ft_make_path(data);
	first(data, fd);
	pipe(fd + 2);
	mid(data, fd, ++i);
	last(data, fd, ++i);
}

int	main(int ac, char **av, char **en)
{
	t_pipex	data;

	ft_bzero(&data, sizeof(t_pipex));
	if (ac < 5)
		return (1);
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		data.here_doc = 1;
	set_data(&data, ac, av, en);
	data.nbr_cmd = 4;
	pipex(&data);
	return (0);
}

//read that dummy
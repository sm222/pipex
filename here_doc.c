/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 09:51:49 by anboisve          #+#    #+#             */
/*   Updated: 2023/04/11 17:59:07 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	hd_star_data(int ac, char **av, char **en, t_pipex *data)
{
	ft_bzero(data, sizeof(t_pipex));
	data->argv = av;
	data->en = en;
	data->argc = ac;
	data->path = ft_make_path(data);
	data->fds = ft_calloc(--ac, sizeof(int *));
	if (!data->fds)
		ft_error("ft_calloc", data);
	while (ac-- - 2)
	{
		data->fds[ac - 1] = ft_calloc(2, sizeof(int));
		if (!data->fds[ac - 1])
			ft_error("ft_calloc", data);
		if (pipe(data->fds[ac - 1]) == -1)
			ft_error("pipe", data);
	}
	data->i++;
}

//O_APPEND

void	make_file_duck(t_pipex data, char *file_out, int fd_in)
{
	open(data.argv[data.argc - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
}

void	here_doc(int ac, char **av, char **en, t_pipex *data)
{
	int		fd[2];
	char	*tmp;

	if (pipe(fd) == -1)
		ft_error("pipe", data);
	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", 1);
		tmp = get_next_line(STDIN_FILENO);
		if (!NULL)
			break ;
		ft_putstr_fd(tmp, fd[1]);
		if (ft_strncmp(tmp, av[2], ft_strlen(av[2] + 1)) == 0)
			break ;
	}
	close(fd[1]);
	hd_star_data(ac, av, en, data);
	close(fd[0]);
}

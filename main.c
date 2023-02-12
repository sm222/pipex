/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:53:36 by anboisve          #+#    #+#             */
/*   Updated: 2023/02/08 12:53:36 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

/*
open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid
*/

int	ft_error(const char *msg)
{
	perror(msg);
	exit(1);
}

char	**ft_make_path(char **en)
{
	size_t	i;
	char	**new;

	i = -1;
	while (en[++i])
		if (!ft_strncmp(en[i], "PATH=", 5))
			break ;
	new = ft_split(en[i] + 5, ':');
	if (!new)
		ft_error("could not find path");
	return (new);
}

char	*ft_find_cmd(char *cmd, char **path)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (!access(cmd, F_OK | X_OK))
		return (cmd);
	while (path[i])
	{
		tmp = ft_combine("%s/%s", path[i], cmd);
		printf("%s\n", tmp);
		if (!access(tmp, F_OK | X_OK))
			break ;
		i++;
		free(tmp);
	}
	return (tmp);
}

int	main(int ac, char **av, char **en)
{
	char	**path;
	int		fd[2];
	pid_t	pid;

	if (ac == 5)
	{
		path = ft_make_path(en);
		if (pipe(fd) < 0)
			ft_error(ERR_PIPE);
		pid = fork();
		if (pid == -1)
			ft_error("could not fork");
		else if (pid == 0)
			ft_find_cmd(av[2], path);
	}
	else
		ft_error("bad arg");
	return (0);
}

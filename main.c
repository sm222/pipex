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

int	ft_error(const char *msg, int type)
{
	if (type)
		printf("error in : %s\n", msg);
	else
		printf("%s\n", msg);
	exit(1);
}

void	ft_child(char **av, char **en, int *fd)
{
	return;
}

int	main(int ac, char **av, char **en)
{
	char	**rez;
	int		fd[2];
	int	i = -1;
	pid_t	pid;

	if (ac == 5)
	{
		if (pipe(fd) < 0)
			ft_error("pipe", 1);
		pid = fork();
		if (pid == -1)
			ft_error("could not fork", 0);
		else if (pid == 0)
			printf(" ");
		
	}
	while (en[++i])
	{
		if (ft_strncmp("PATH=", en[i], 5) == 0)
			break ;
	}
	en = ft_split(en[i],':');
	i = -1;
	while (en[++i])
		printf("%s\n", en[i]);
	return(0);
}

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
		ft_error(sys_errlist[sys_nerr]);
	return (new);
}

char	*ft_find_cmd(char *cmd, char **path)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (!access(cmd, F_OK | X_OK))
		return (ft_strdup(cmd));
	while (path[i])
	{
		tmp = ft_combine("%s/%s", path[i], cmd);
		if (!access(tmp, F_OK | X_OK))
			return (tmp);
		tmp = ft_safe_free(tmp);
		i++;
	}
	return (NULL);
}

void	ft_chek_file(t_pipex *data)
{
	data->input = open(data->argv[1], O_RDONLY);
	if (data->input < 0)
		ft_error("ft_chek_file , file 1");
	data->output = open(data->argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->output < 0)
		ft_error("ft_chek_file , file 2");
}

void	ft_chek_cmd(t_pipex *data)
{
	char	*c1;
	char	*c2;

	data->cmd1 = ft_split(data->argv[2], ' ');
	c1 = ft_find_cmd(data->cmd1[0], data->path);
	if (!c1)
		ft_error("can't fine first commend");
	c1 = ft_safe_free(c1);
	//execve(ft_find_cmd(data->cmd1[0], data->path), data->cmd1, data->path);
	data->cmd2 = ft_split(data->argv[3], ' ');
	c2 = ft_find_cmd(data->cmd2[0], data->path);
	if (!c2)
		ft_error("can't fine segond commend");
	c2 = ft_safe_free(c2);
	data->cmd1 = (char **)ft_double_sfree((void **)data->cmd1);
	data->cmd2 = (char **)ft_double_sfree((void **)data->cmd2);
}

void	ft_child1(t_pipex *data)
{
	char	*p;
	char	**ex;

	dup2(data->input, STDIN_FILENO);
	dup2(data->output, STDOUT_FILENO);
	close(data->fd[0]);
	close(data->fd[1]);
	ex = ft_split(data->argv[2], ' ');
	p = ft_find_cmd(data->argv[1], data->path);
	execve(p, ex, data->en);
}

void	ft_child2(t_pipex *data)
{
	char	*p;
	char	**ex;

	dup2(data->output, STDOUT_FILENO);
	dup2(data->pid[0], STDIN_FILENO);
	close(data->fd[0]);
	close(data->fd[1]);
	ex = ft_split(data->argv[2], ' ');
	p = ft_find_cmd(data->argv[1], data->path);
	execve(p, ex, data->en);
}

int	main(int ac, char **av, char **en)
{
	t_pipex	data;

	data.argv = av;
	data.en = en;
	if (ac == 5)
	{
		data.path = ft_make_path(en);
		if (!data.path)
			ft_error("can't find path");
		ft_chek_cmd(&data);
		ft_chek_file(&data);
		if (pipe(&data.fd[0]) != 0)
			ft_error("can't make the pipe");
		data.pid[0] = fork();
		if (data.pid[0] == 0)
			ft_child1(&data);
		data.pid[1] = fork();
		if (data.pid[1] == 0)
			ft_child2(&data);
		waitpid(data.pid[0], NULL, 0);
		waitpid(data.pid[1], NULL, 0);
	}
	else
		ft_error("need 4 argv");
	return (0);
}

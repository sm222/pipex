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
	if (sys_nerr)
		perror(msg);
	else
		ft_printf("%s", msg);
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
	if (en[i][0] == 0)
		ft_error(sys_errlist[sys_nerr]);
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
	tmp = ft_combine("./%s", cmd);
	if (!access(cmd, F_OK | X_OK))
		return (tmp);
	tmp = ft_safe_free(tmp);
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
	data->cmd2 = ft_split(data->argv[3], ' ');
	c2 = ft_find_cmd(data->cmd2[0], data->path);
	if (!c2)
		ft_error("can't fine segond commend");
	c2 = ft_safe_free(c2);
}

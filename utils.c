/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:37:50 by anboisve          #+#    #+#             */
/*   Updated: 2023/02/20 16:37:50 by anboisve         ###   ########.fr       */
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

void	ft_free_data(t_pipex *data)
{
	if (!data)
		return ;
	ft_double_sfree((void **)data->path);
	data->argv = NULL;
	data->en = NULL;
}

int	ft_error(const char *msg, t_pipex *data)
{
	perror(msg);
	ft_free_data(data);
	exit(errno);
}

char	**ft_make_path(t_pipex *data)
{
	size_t	i;
	char	**new;

	new = NULL;
	i = 0;
	while (data->en[i])
	{
		if (ft_strncmp(data->en[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (data->en[i] != NULL)
		new = ft_split(data->en[i] + 5, ':');
	if (!new)
		ft_error(sys_errlist[errno], data);
	return (new);
}

char	*ft_find_cmd(char *cmd, char **path)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	tmp = ft_combine("./%s", cmd);
	if (access(cmd, F_OK | X_OK) == 0)
		return (tmp);
	tmp = ft_safe_free(tmp);
	while (path[i])
	{
		tmp = ft_combine("%s/%s", path[i], cmd);
		if (access(tmp, F_OK | X_OK) == 0)
			return (tmp);
		tmp = ft_safe_free(tmp);
		i++;
	}
	return (NULL);
}

void	ft_check_file(t_pipex *data)
{
	data->input = open(data->argv[1], O_RDONLY);
	if (data->input < 0)
		ft_error(data->argv[1], data);
	data->output = open(data->argv[data->argc - 1] \
	, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->output < 0)
		ft_error(data->argv[data->argc - 1], data);
}

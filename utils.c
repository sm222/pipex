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
end the program and free the memory, send the error on stderr(2)
*/
void	ft_exit(t_pipex *data, int err, char *msg)
{
	ft_double_sfree((void **)data->path);
	ft_close_fds(data->pipes, 1, data->nbr_pipes);
	free_pid(&data->pids);
	if (msg)
		perror(msg);
	exit(err);
}

/*
look the environment to find the paths of the system
*/
char	**ft_make_path(t_pipex *data)
{
	size_t	i;
	char	**new;

	i = 0;
	new = NULL;
	while (data->en[i])
	{
		if (ft_strncmp(data->en[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (data->en[i] != NULL)
		new = ft_split(data->en[i] + 5, ':');
	if (!new)
		return (NULL);
	return (new);
}

/*
use the path and the name of the command and try to find it location
*/
char	*ft_find_cmd(char *cmd, char **path)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	tmp = ft_combine("./%s", cmd);
	if (!tmp)
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0)
		return (tmp);
	tmp = ft_safe_free(tmp);
	while (path[i])
	{
		tmp = ft_combine("%s/%s", path[i], cmd);
		if (!tmp)
			return (NULL);
		if (access(tmp, F_OK | X_OK) == 0)
			return (tmp);
		tmp = ft_safe_free(tmp);
		i++;
	}
	return (ft_combine("can,t find %s", cmd));
}

/*
take the address of a double pointer int and open the amount of (int size).
return -1 if malloc or pipe fail or the number of pipe if success
*/
int	make_pipes(int size, int ***pipes)
{
	int	i;
	int	**fd;

	i = 0;
	if (size < 1)
		return (0);
	fd = ft_calloc(size, sizeof(int *));
	if (!fd)
		return (-1);
	while (i < size)
	{
		fd[i] = ft_calloc(2, sizeof(int));
		if (!fd[i] || pipe(fd[i]) == -1)
		{
			ft_close_fds(fd, 1, i);
			return (-1);
		}
		i++;
	}
	*pipes = fd;
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:54:33 by anboisve          #+#    #+#             */
/*   Updated: 2023/02/08 12:54:33 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "lib_ft/libft.h"
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

# define ERR_PIPE "can't open the fd in pipe"
# define ERR_ICI "ici"

typedef struct s_pids
{
	pid_t			pid;
	struct s_pids	*next;
}	t_pids;

typedef struct s_pipex
{
	int		input;
	int		output;
	char	**path;
	char	**argv;
	int		argc;
	char	**en;
	int		**fds;
	t_pids	*pids;
}			t_pipex;

void	ft_check_file(t_pipex *data);
char	*ft_find_cmd(char *cmd, char **path);
char	**ft_make_path(t_pipex *data);
int		ft_error(const char *msg, t_pipex *data);
void	ft_free_data(t_pipex *data);

void	run_cmd(char *cmd, char **path, t_pipex *data);
void	child(t_pipex *data, char *cmd, int i);

//

int		make_pid_node(t_pids **head, pid_t pid);
void	free_pid(t_pids	**pids);

#endif
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
	char	**en;
	int		**pipes;
	int		argc;
	int		here_doc;
	t_pids	*pids;
	int		nbr_cmd;

}			t_pipex;

char	*ft_find_cmd(char *cmd, char **path);
char	**ft_make_path(t_pipex *data);

//
void	free_pid(t_pids	**pids);
void	wait_node(t_pids **head);
int		make_pid_node(t_pids **head, pid_t pid);
void	ft_exit(t_pipex *data, int err, char *msg);
void	run_cmd(char *cmd, char **path, t_pipex *data);
void	first(t_pipex *data, int fd_i, int index);
void	mid(t_pipex *data, int fd_i, int index);
int		make_pipes(int size, int ***pipes);

//

#endif

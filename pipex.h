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
# include <sys/wait.h>

# define ERR_PIPE "can't open the fd in pipe"

typedef struct s_pipex
{
	int		input;
	int		output;
	char	**path;
	char	**argv;
	char	**en;
	char	**cmd1;
	char	**cmd2;
	int		pipe[2];
	pid_t	pid[2];

}	t_pipex;

int		ft_error(const char *msg);
void	ft_child1(t_pipex *data);
void	ft_child2(t_pipex *data);
char	**ft_make_path(char **en);
char	*ft_find_cmd(char *cmd, char **path);
void	ft_chek_file(t_pipex *data);
void	ft_chek_cmd(t_pipex *data);

#endif // PIPEX_H

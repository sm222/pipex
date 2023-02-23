/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:57:06 by anboisve          #+#    #+#             */
/*   Updated: 2023/02/23 17:57:27 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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

void	ft_free_data(t_pipex *data);
int		ft_error(const char *msg, t_pipex *data);
void	ft_child1(t_pipex *data);
void	ft_child2(t_pipex *data);
char	**ft_make_path(t_pipex *data);
char	*ft_find_cmd(char *cmd, t_pipex *data);
void	ft_check_file(t_pipex *data);

#endif // PIPEX_BONUS_H

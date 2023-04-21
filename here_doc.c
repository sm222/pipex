/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:12:06 by anboisve          #+#    #+#             */
/*   Updated: 2023/04/21 17:50:35 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(t_pipex *data)
{
	pid_t	new;
	char	*tmp;

	data->input = open("/tmp/here_doc", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (data->input < 0)
		ft_exit(data, 1, "can't make here_doc");
	new = fork();
	if (new == -1)
		ft_exit(data, errno, "fork");
	if (new == 0)
	{
		while (1)
		{
			ft_putstr_fd("here_doc >", 1);
			tmp = get_next_line(0);
			if (ft_strncmp(tmp, data->argv[2], \
			ft_strlen(data->argv[2]) + 1) == 0)
				break ;
			ft_putstr_fd(tmp, data->input);
			ft_safe_free(tmp);
		}
	}
	else
	{
		close(data->input);
		waitpid(new, NULL, 0);
	}
}
